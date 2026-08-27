# Copyright (C) 2026 Devin Shwagginz
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# ==> The entry point for Doo-cr

require "socket"

require "./doo-cr/lib.cr"
require "./doo-cr/variables.cr"
require "./doo-cr/doo-cr.cr"
require "./doo-cr/implementation.cr"

require "raylib-cr"
require "raylib-cr/audio.cr"
require "./adlmidi.cr"

module LibDoom
  VERSION_STR = "1.0"
  VERSION = 10

  # The resolutions of the render target the screen puts on the screen
  SRES_X = 320
  SRES_Y = 240

  # Midi info
  MIDI_BUFFER_SIZE =  2048
  MIDI_SAMPLE_RATE = 44100
  MIDI_TICK_TIME   = 1.0 / 140.0
  # TODO: make a setting
  MIDI_BANK        = 16

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

  @@execsize = 1

  unless ARGV.includes?("-nosound")
    CDoom.i_error("Error: Cannot run sounds with less than #{@@execsize} cpu cores!\nUse -nosound to run.") if System.cpu_count < (@@execsize += 1)

    audio_context = Fiber::ExecutionContext::Isolated.new("doom-audio") do
      LibDoom.update_audio
    end
  end

  if ARGV.includes?("-net")
    CDoom.i_error("Error: cannot run netgame with less than #{@@execsize} cpu cores!") if System.cpu_count < (@@execsize += 1)

    net_context = Fiber::ExecutionContext::Isolated.new("doom-net") do
      until @@insocket
      end
      sock = @@insocket.not_nil!
      loop do
        sw_ptr = GC.malloc(sizeof(CDoom::Doomdata)).as(CDoom::Doomdata*)
        buf = Bytes.new(sw_ptr.as(UInt8*), sizeof(CDoom::Doomdata))
        begin
          c, fromaddress = sock.receive(buf)
          @@recv_channel.send({sw_ptr.value, c, fromaddress})
        rescue ex
        end
      end
    end
  end
end

LibDoom.doom_init(ARGC_UNSAFE, ARGV_UNSAFE, 0)
