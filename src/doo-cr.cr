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
require "uing"
require "raudio"

require "./doo-cr/lib.cr"
require "./doo-cr/variables.cr"
require "./doo-cr/doo-cr.cr"
require "./doo-cr/implementation.cr"

require "./adlmidi.cr"

# Load fork-specific backends after the upstream implementation. Crystal's
# open types let these files replace only the platform methods they own.
require "./doo-cr/backends/uing.cr"
require "./doo-cr/backends/raudio.cr"

module LibDoom
  record MouseDelta, x : Int32, y : Int32

  VERSION_STR = "1.3" # Used for displaying
  DEMOVERSION = 110
  SAVEVERSION =  10
  NETVERSION  =  13

  unless ARGV.includes?("-nosound")
    # Create a separate thread so audio updates separately from game code
    audio_context = Fiber::ExecutionContext::Isolated.new("doom-audio") do
      LibDoom.update_audio
    end
  end

  @@pause_socket = false
  if ARGV.includes?("-net") || ARGV.includes?("-altnet")
    # Create a separate thread for the packets-in buffer during a netgame
    net_context = Fiber::ExecutionContext::Isolated.new("doom-net") do
      until @@insocket
      end
      sock = @@insocket.not_nil!
      loop do
        next if @@pause_socket
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

struct SpinLock
  def initialize
    @flag = Atomic(Bool).new(false)
  end

  def synchronize(&)
    until @flag.compare_and_set(false, true)[1]
      LibC.sched_yield # let another OS thread run; does NOT touch Crystal's fiber scheduler
    end
    begin
      yield
    ensure
      @flag.set(false)
    end
  end
end

lib LibC
  fun sched_yield : Int32
end

Fiber::ExecutionContext.default.resize(1)

# Make it happen!
LibDoom.doom_init(ARGC_UNSAFE, ARGV_UNSAFE, 0)
