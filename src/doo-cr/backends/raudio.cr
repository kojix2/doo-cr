module LibDoom
  AUDIO_CHANNELS        =  2
  AUDIO_SAMPLE_BITS     = 16
  SFX_CHUNK_FRAMES      = CDoom::SAMPLECOUNT
  SFX_BUFFER_CHUNKS     = 2
  SFX_BUFFER_FRAMES     = SFX_CHUNK_FRAMES * SFX_BUFFER_CHUNKS
  SFX_CHUNK_SAMPLES     = SFX_CHUNK_FRAMES * AUDIO_CHANNELS
  SFX_BUFFER_SAMPLES    = SFX_BUFFER_FRAMES * AUDIO_CHANNELS
  MIDI_SAMPLE_RATE      = 44100
  MIDI_TICKS_PER_SECOND =   140
  MIDI_BUFFER_FRAMES    =  1024
  MIDI_BUFFER_SAMPLES   = MIDI_BUFFER_FRAMES * AUDIO_CHANNELS
  MIDI_FRAMES_PER_TICK  = MIDI_SAMPLE_RATE // MIDI_TICKS_PER_SECOND
  MIDI_BANK             = 16 # TODO: make this configurable

  @@sfx_stream : Raudio::AudioStream?
  @@sfx_buffer = Pointer(Int16).null
  @@adl_player : ADLMIDI::Player*?
  @@music_stream : Raudio::AudioStream?
  @@music_buffer = Pointer(Int16).null
  @@midi_frames_until_tick = 0

  def self.i_set_music_volume(volume : Int32)
    CDoom.mus_volume = CDoom.snd_music_volume * 8

    if @@mus_is_midi
      @@music_stream.try { |stream| stream.volume = (volume / 15.0).to_f32 }
    else
      @@music_stream.try { |stream| stream.volume = 1.0_f32 }

      16.times do |channel|
        volume_message = 0x000000B0_u32 | channel | 0x0700_u32 |
                         (((CDoom.mus_channel_volumes[channel] * CDoom.mus_volume) // 127) << 16)
        CDoom.queued_midi_msgs[CDoom.queue_midi_tail % CDoom::MAX_QUEUED_MIDI_MSGS] = volume_message
        CDoom.queue_midi_tail += 1
      end
    end
  end

  def self.i_shutdown_sound
    deadline = i_get_time + 70
    print "i_shutdown_sound: Finishing pending sounds..."

    loop do
      if CDoom.num_channels.times.all? { |channel| CDoom.channels[channel].null? }
        puts " finished!"
        break
      end

      if i_get_time > deadline
        puts " couldn't finish."
        break
      end
    end

    @@sfx_stream.try &.release
    @@sfx_stream = nil
    @@sfx_buffer = Pointer(Int16).null
  end

  private def self.dispatch_midi_message(player : ADLMIDI::Player*, message : UInt64)
    status = (message & 0xFF).to_u8
    data1 = ((message >> 8) & 0xFF).to_u8
    data2 = ((message >> 16) & 0xFF).to_u8
    command = status & 0xF0
    channel = status & 0x0F

    case command
    when 0x80
      ADLMIDI.adl_rt_noteOff(player, channel, data1)
    when 0x90
      if data2 == 0
        ADLMIDI.adl_rt_noteOff(player, channel, data1)
      else
        ADLMIDI.adl_rt_noteOn(player, channel, data1, data2)
      end
    when 0xA0
      ADLMIDI.adl_rt_noteAfterTouch(player, channel, data1, data2)
    when 0xB0
      ADLMIDI.adl_rt_controllerChange(player, channel, data1, data2)
    when 0xC0
      ADLMIDI.adl_rt_patchChange(player, channel, data1)
    when 0xD0
      ADLMIDI.adl_rt_channelAfterTouch(player, channel, data1)
    when 0xE0
      ADLMIDI.adl_rt_pitchBendML(player, channel, data2, data1)
    end
  end

  private def self.fill_mus_buffer(player : ADLMIDI::Player*)
    frames_written = 0

    while frames_written < MIDI_BUFFER_FRAMES
      # Drive MUS timing from generated audio rather than scheduler time.
      if @@midi_frames_until_tick == 0
        while (message = CDoom.doom_tick_midi) != 0
          dispatch_midi_message(player, message)
        end
        @@midi_frames_until_tick = MIDI_FRAMES_PER_TICK
      end

      frames = {MIDI_BUFFER_FRAMES - frames_written, @@midi_frames_until_tick}.min
      sample_offset = frames_written * AUDIO_CHANNELS
      ADLMIDI.adl_generate(player, frames * AUDIO_CHANNELS, @@music_buffer + sample_offset)
      frames_written += frames
      @@midi_frames_until_tick -= frames
    end
  end

  private def self.fill_sfx_buffer
    # The Doom mixer emits one chunk at a time. Combine two chunks so the
    # stream is not padded with silence on devices with larger periods.
    SFX_BUFFER_CHUNKS.times do |chunk|
      source = CDoom.doom_get_sound_buffer
      destination = @@sfx_buffer + chunk * SFX_CHUNK_SAMPLES
      destination.copy_from(source, SFX_CHUNK_SAMPLES)
    end
  end

  private def self.refill_music_stream(stream : Raudio::AudioStream, player : ADLMIDI::Player*)
    while stream.processed?
      if @@mus_is_midi
        ADLMIDI.adl_play(player, MIDI_BUFFER_SAMPLES, @@music_buffer)
      else
        fill_mus_buffer(player)
      end
      stream.update(@@music_buffer.as(Void*), MIDI_BUFFER_FRAMES)
    end
  end

  private def self.refill_sfx_stream(stream : Raudio::AudioStream)
    while stream.processed?
      fill_sfx_buffer
      stream.update(@@sfx_buffer.as(Void*), SFX_BUFFER_FRAMES)
    end
  end

  private def self.create_audio_stream(sample_rate : UInt32, buffer_frames : Int32)
    Raudio::AudioStream.buffer_size_default = buffer_frames
    stream = Raudio::AudioStream.load(sample_rate, AUDIO_SAMPLE_BITS.to_u32, AUDIO_CHANNELS.to_u32)
    stream.volume = 1.0_f32
    stream.play
    stream
  end

  def self.update_audio
    loop do
      return if @@closing

      sfx_stream = @@sfx_stream
      music_stream = @@music_stream
      player = @@adl_player
      unless @@ui_initialized && Raudio::AudioDevice.ready? &&
             sfx_stream && music_stream && player
        sleep 1.millisecond
        next
      end

      refill_music_stream(music_stream, player) if CDoom.mus_playing != 0

      return if @@closing
      refill_sfx_stream(sfx_stream)
      sleep 1.millisecond
    end
  end

  def self.i_init_sound
    print "i_init_sound: "

    i = 1
    while i < CDoom::Sfxenum::NUMSFX.value
      if (CDoom.s_sfx + i).value.link.null?
        (CDoom.s_sfx + i).value.data = CDoom.getsfx((CDoom.s_sfx + i).value.name, CDoom.lengths.to_unsafe + i)
      else
        (CDoom.s_sfx + i).value.data = (CDoom.s_sfx + i).value.link.value.data
        CDoom.lengths[i] = CDoom.lengths[((CDoom.s_sfx + i).value.link - CDoom.s_sfx) // sizeof(CDoom::Sfxinfo)]
      end
      i += 1
    end

    puts "Pre-cached all sound data"
    CDoom::MIXBUFFERSIZE.times { |index| CDoom.mixbuffer[index] = 0 }

    Raudio::AudioDevice.init
    Raudio::AudioDevice.master_volume = 1.0_f32
    @@sfx_buffer = Pointer(Int16).malloc(SFX_BUFFER_SAMPLES)
    @@sfx_stream = create_audio_stream(CDoom::DOOM_SAMPLERATE.to_u32, SFX_BUFFER_FRAMES)

    puts "i_init_sound: sound module ready"
  end

  def self.i_init_music
    player = ADLMIDI.adl_init(MIDI_SAMPLE_RATE)
    ADLMIDI.adl_setNumChips(player, 4)
    ADLMIDI.adl_setBank(player, MIDI_BANK)
    ADLMIDI.adl_setSoftPanEnabled(player, @@midismoothpan)

    @@music_buffer = Pointer(Int16).malloc(MIDI_BUFFER_SAMPLES)
    @@midi_frames_until_tick = 0
    @@music_stream = create_audio_stream(MIDI_SAMPLE_RATE.to_u32, MIDI_BUFFER_FRAMES)
    @@adl_player = player
  end

  def self.i_shutdown_music
    @@music_stream.try &.release
    @@music_stream = nil
    @@adl_player.try { |player| ADLMIDI.adl_close(player) }
    @@adl_player = nil
    @@music_buffer = Pointer(Int16).null
    @@midi_frames_until_tick = 0
  end

  def self.i_play_song(handle : Int32, looping : Int32)
    i_set_music_volume(CDoom.snd_music_volume)
    @@midi_frames_until_tick = 0

    CDoom.musicdies = CDoom.gametic + CDoom::TICRATE * 30
    CDoom.mus_loop = looping != 0 ? 1 : 0
    CDoom.mus_playing = 1
    if @@mus_is_midi
      @@adl_player.try do |player|
        ADLMIDI.adl_openData(player, CDoom.mus_data, w_lump_length(CDoom.mus_playing_s_sound.value.lumpnum))
      end
    end
  end

  def self.i_stop_song(handle : LibC::Int)
    CDoom.mus_data = Pointer(UInt8).null
    CDoom.mus_delay = 0
    CDoom.mus_offset = 0
    CDoom.mus_playing = 0
    @@mus_is_midi = false
    @@midi_frames_until_tick = 0
    @@adl_player.try { |player| ADLMIDI.adl_panic(player) }
    @@adl_player.try { |player| ADLMIDI.adl_reset(player) }
    CDoom.reset_all_channels
  end

  def self.i_quit
    @@closing = true
    CDoom.d_quit_net_game
    CDoom.i_shutdown_sound
    CDoom.i_shutdown_music
    Raudio::AudioDevice.close
    CDoom.m_save_defaults
    CDoom.i_shutdown_graphics
    CDoom.doom_exit.call(0)
  end
end
