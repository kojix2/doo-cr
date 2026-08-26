require "socket"

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
  LibDoom.doom_key_up(CDoom::DoomKey::{{doomkey}}) if Raylib::KeyboardKey::{{raylibkey}}.released?
  LibDoom.doom_key_down(CDoom::DoomKey::{{doomkey}}) if Raylib::KeyboardKey::{{raylibkey}}.pressed?
end

macro poll_button(doombutton, raylibbutton)
  LibDoom.doom_button_up(CDoom::DoomButton::{{doombutton}}) if Raylib::MouseButton::{{raylibbutton}}.released?
  LibDoom.doom_button_down(CDoom::DoomButton::{{doombutton}}) if Raylib::MouseButton::{{raylibbutton}}.pressed?
end

Fiber::ExecutionContext.default.resize(maximum: 1)

spawn { LibDoom.doom_init(ARGC_UNSAFE, ARGV_UNSAFE, 0) }
spawn { LibDoom.update_audio } # virtual sound card thread

sleep
