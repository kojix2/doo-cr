require "socket"
require "http/client"

require "./doo-cr/lib.cr"
require "./doo-cr/variables.cr"
require "./doo-cr/doo-cr.cr"
require "./doo-cr/implementation.cr"

require "raylib-cr"
require "raylib-cr/audio.cr"
require "./adlmidi.cr"

SRES_X = 320
SRES_Y = 240

MIDI_BUFFER_SIZE =  2048
MIDI_SAMPLE_RATE = 44100
MIDI_TICK_TIME   = 1.0 / 140.0
MIDI_BANK        = 16

# If rangecheck is undefined,
# most parameter validation debugging code will not be compiled
RANGECHECK = true

macro poll_key(doomkey, raylibkey)
  was_down = LibDoom.keystates[CDoom::DoomKey::{{doomkey}}.value]
  is_down = Raylib::KeyboardKey::{{raylibkey}}.down?

  LibDoom.doom_key_down(CDoom::DoomKey::{{doomkey}}) if is_down && !was_down
  LibDoom.doom_key_up(CDoom::DoomKey::{{doomkey}}) if !is_down && was_down
end

macro poll_two_key(doomkey, raylibkey1, raylibkey2)
  was_down = LibDoom.keystates[CDoom::DoomKey::{{doomkey}}.value]
  is_down = Raylib::KeyboardKey::{{raylibkey1}}.down? || Raylib::KeyboardKey::{{raylibkey2}}.down?
  
  LibDoom.doom_key_down(CDoom::DoomKey::{{doomkey}}) if is_down && !was_down
  LibDoom.doom_key_up(CDoom::DoomKey::{{doomkey}}) if !is_down && was_down
end

macro poll_button(doombutton, raylibbutton)
  was_down = CDoom.button_states[CDoom::DoomButton::{{doombutton}}.value] != 0
  is_down = Raylib::MouseButton::{{raylibbutton}}.down?
  LibDoom.doom_button_down(CDoom::DoomButton::{{doombutton}}) if is_down && !was_down
  LibDoom.doom_button_up(CDoom::DoomButton::{{doombutton}}) if !is_down && was_down
end


unless ARGV.includes?("-nosound")
  CDoom.i_error("Error: Cannot run sounds with less than 2 cpu cores!\nUse -nosound to run.") if System.cpu_count < 2
  Fiber::ExecutionContext.default.resize(maximum: 2)

  spawn { LibDoom.update_audio } # virtual sound card thread
end

LibDoom.doom_init(ARGC_UNSAFE, ARGV_UNSAFE, 0)
