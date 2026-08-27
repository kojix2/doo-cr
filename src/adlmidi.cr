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
# ==> Bindings to libADLMIDI https://github.com/Wohlstand/libADLMIDI

@[Link(ldflags: "-L#{__DIR__}/../rsrc -lADLMIDI")]
lib ADLMIDI
  alias Player = Void

  fun adl_init(sample_rate : LibC::Long) : Player*
  fun adl_close(device : Player*) : Void
  fun adl_setNumChips(device : Player*, num_chips : LibC::Int) : LibC::Int
  fun adl_setBank(device : Player*, bank : LibC::Int) : LibC::Int
  fun adl_errorInfo(device : Player*) : LibC::Char* # check this on any negative return
  fun adl_openData(device : Player*, mem : Void*, size : LibC::ULong) : LibC::Int
  fun adl_play(device : Player*, sampleCount : LibC::Int, out_buf : Int16*) : LibC::Int
  fun adl_panic(device : Player*) : Void
  fun adl_reset(device : Player*) : Void
  fun adl_positionRewind(device : Player*) : Void

  fun adl_rt_resetState(device : Player*) : Void
  fun adl_rt_noteOn(device : Player*, channel : UInt8, note : UInt8, velocity : UInt8) : LibC::Int
  fun adl_rt_noteOff(device : Player*, channel : UInt8, note : UInt8) : Void
  fun adl_rt_noteAfterTouch(device : Player*, channel : UInt8, note : UInt8, at_val : UInt8) : Void
  fun adl_rt_channelAfterTouch(device : Player*, channel : UInt8, at_val : UInt8) : Void
  fun adl_rt_controllerChange(device : Player*, channel : UInt8, type : UInt8, value : UInt8) : Void
  fun adl_rt_patchChange(device : Player*, channel : UInt8, patch : UInt8) : Void
  fun adl_rt_pitchBendML(device : Player*, channel : UInt8, msb : UInt8, lsb : UInt8) : Void
  fun adl_setSoftPanEnabled(device : Void*, softPanEn : LibC::Int) : Void

  fun adl_generate(device : Player*, sample_count : LibC::Int, out : Int16*) : LibC::Int
end
