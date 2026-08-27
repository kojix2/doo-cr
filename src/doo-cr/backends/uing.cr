module LibDoom
  SRES_X = 320
  SRES_Y = 240

  @@ui_window : UIng::Window?
  @@ui_area : UIng::Area?
  @@ui_handler : UIng::Area::Handler?
  @@screen_image : UIng::Image?
  @@ui_initialized = false
  @@frame_pixels = Bytes.new(CDoom::SCREENWIDTH * CDoom::SCREENHEIGHT * 4)

  @@last_mouse_x : Float64? = nil
  @@last_mouse_y : Float64? = nil

  # Keep the upstream software-rendering path active. The uing backend only
  # replaces presentation, not Doom's indexed framebuffer renderer.
  @@software_rendering = true
  @@software_screen = Bytes.new(CDoom::SCREENWIDTH * CDoom::SCREENHEIGHT)

  def self.doom_draw
    return unless @@ui_initialized

    screen = CDoom.screens[0]
    pixels = @@frame_pixels.to_unsafe.as(UInt32*)
    palette = @@palette_rgba.to_unsafe

    (CDoom::SCREENWIDTH * CDoom::SCREENHEIGHT).times do |offset|
      pixels[offset] = palette[screen[offset]]
    end

    draw_crosshair(pixels)

    image = UIng::Image.new(CDoom::SCREENWIDTH, CDoom::SCREENHEIGHT)
    image.append(@@frame_pixels, CDoom::SCREENWIDTH, CDoom::SCREENHEIGHT, CDoom::SCREENWIDTH * 4)
    old_image = @@screen_image
    @@screen_image = image
    old_image.try &.free
    @@ui_area.try &.queue_redraw_all
  end

  private def self.draw_crosshair(pixels : UInt32*)
    return if CDoom.crosshair == 0 ||
              CDoom.menuactive != 0 ||
              CDoom.gamestate != CDoom::Gamestate::Level ||
              CDoom.automapactive != 0

    x = CDoom::SCREENWIDTH // 2
    y = CDoom::SCREENHEIGHT // 2
    y += CDoom.setblocks == 11 ? 8 : -8
    white = 0xffffffff_u32

    2.times do |offset|
      pixels[y * CDoom::SCREENWIDTH + x - 2 - offset] = white
      pixels[y * CDoom::SCREENWIDTH + x + 2 + offset] = white
      pixels[(y - 2 - offset) * CDoom::SCREENWIDTH + x] = white
      pixels[(y + 2 + offset) * CDoom::SCREENWIDTH + x] = white
    end
  end

  def self.platform_step : Bool
    running = UIng.main_step(false)
    @@closing = true unless running
    running
  end

  def self.doom_key_down(key : CDoom::DoomKey)
    return if @@keystates[key.value]

    @@keystates[key.value] = true
    event = CDoom::Event.new
    event.type = CDoom::Evtype::Keydown
    event.data1 = key.value
    CDoom.d_post_event(pointerof(event))
  end

  def self.doom_key_up(key : CDoom::DoomKey)
    return unless @@keystates[key.value]

    @@keystates[key.value] = false
    event = CDoom::Event.new
    event.type = CDoom::Evtype::Keyup
    event.data1 = key.value
    CDoom.d_post_event(pointerof(event))
  end

  def self.i_shutdown_graphics
    return unless @@ui_initialized

    @@closing = true
    @@screen_image.try &.free
    @@screen_image = nil
    @@ui_window.try do |window|
      window.destroy unless window.released?
    end
    @@ui_area = nil
    @@ui_handler = nil
    @@ui_window = nil
    UIng.uninit
    @@ui_initialized = false
  end

  def self.i_start_frame
  end

  def self.i_poll_mouse
  end

  def self.i_start_tic(in_delta : MouseDelta? = nil)
    mouse_delta = in_delta || @@mouse_queued
    doom_mouse_move(mouse_delta.x, mouse_delta.y)
    @@mouse_queued = MouseDelta.new(0, 0) unless in_delta
  end

  def self.i_read_screen(screen : CDoom::Byte*)
    CDoom.doom_memcpy(screen, CDoom.screens[0], CDoom::SCREENWIDTH * CDoom::SCREENHEIGHT)
  end

  def self.i_set_palette(palette : CDoom::Byte*)
    256.times do |index|
      red = CDoom.gammatable[CDoom.usegamma][palette.value] & ~3
      palette += 1
      green = CDoom.gammatable[CDoom.usegamma][palette.value] & ~3
      palette += 1
      blue = CDoom.gammatable[CDoom.usegamma][palette.value] & ~3
      palette += 1

      CDoom.screen_palette[index * 3] = red
      CDoom.screen_palette[index * 3 + 1] = green
      CDoom.screen_palette[index * 3 + 2] = blue
      @@palette_rgba[index] = (255_u32 << 24) | (blue.to_u32 << 16) | (green.to_u32 << 8) | red.to_u32
    end
  end

  private def self.handle_ui_key(event : UIng::Area::KeyEvent)
    key = case event.modifier
          when UIng::Area::Modifiers::Ctrl  then CDoom::DoomKey::CTRL
          when UIng::Area::Modifiers::Alt   then CDoom::DoomKey::ALT
          when UIng::Area::Modifiers::Shift then CDoom::DoomKey::SHIFT
          else                                   doom_key_from_ui(event)
          end
    return unless key

    event.up == 0 ? doom_key_down(key) : doom_key_up(key)
  end

  private def self.doom_key_from_ui(event : UIng::Area::KeyEvent) : CDoom::DoomKey?
    ext_key = case event.ext_key
              when UIng::Area::ExtKey::Escape    then CDoom::DoomKey::ESCAPE
              when UIng::Area::ExtKey::Left      then CDoom::DoomKey::LEFT_ARROW
              when UIng::Area::ExtKey::Up        then CDoom::DoomKey::UP_ARROW
              when UIng::Area::ExtKey::Right     then CDoom::DoomKey::RIGHT_ARROW
              when UIng::Area::ExtKey::Down      then CDoom::DoomKey::DOWN_ARROW
              when UIng::Area::ExtKey::F1        then CDoom::DoomKey::F1
              when UIng::Area::ExtKey::F2        then CDoom::DoomKey::F2
              when UIng::Area::ExtKey::F3        then CDoom::DoomKey::F3
              when UIng::Area::ExtKey::F4        then CDoom::DoomKey::F4
              when UIng::Area::ExtKey::F5        then CDoom::DoomKey::F5
              when UIng::Area::ExtKey::F6        then CDoom::DoomKey::F6
              when UIng::Area::ExtKey::F7        then CDoom::DoomKey::F7
              when UIng::Area::ExtKey::F8        then CDoom::DoomKey::F8
              when UIng::Area::ExtKey::F9        then CDoom::DoomKey::F9
              when UIng::Area::ExtKey::F10       then CDoom::DoomKey::F10
              when UIng::Area::ExtKey::F11       then CDoom::DoomKey::F11
              when UIng::Area::ExtKey::F12       then CDoom::DoomKey::F12
              when UIng::Area::ExtKey::NMultiply then CDoom::DoomKey::MULTIPLY
              else                                    nil
              end
    return ext_key if ext_key

    char = event.key.downcase
    return CDoom::DoomKey.new(char.ord) if ('a'..'z').includes?(char) || ('0'..'9').includes?(char)

    case char
    when '\t'           then CDoom::DoomKey::TAB
    when '\r', '\n'     then CDoom::DoomKey::ENTER
    when ' '            then CDoom::DoomKey::SPACE
    when '\''           then CDoom::DoomKey::APOSTROPHE
    when ','            then CDoom::DoomKey::COMMA
    when '-'            then CDoom::DoomKey::MINUS
    when '.'            then CDoom::DoomKey::PERIOD
    when '/'            then CDoom::DoomKey::SLASH
    when ';'            then CDoom::DoomKey::SEMICOLON
    when '='            then CDoom::DoomKey::EQUALS
    when '['            then CDoom::DoomKey::LEFT_BRACKET
    when ']'            then CDoom::DoomKey::RIGHT_BRACKET
    when '\b', '\u007f' then CDoom::DoomKey::BACKSPACE
    else                     nil
    end
  end

  private def self.handle_ui_mouse(event : UIng::Area::MouseEvent)
    if last_x = @@last_mouse_x
      @@mouse_queued = MouseDelta.new(
        @@mouse_queued.x + ((event.x - last_x) * 2).to_i32,
        @@mouse_queued.y
      )
    end
    if last_y = @@last_mouse_y
      @@mouse_queued = MouseDelta.new(
        @@mouse_queued.x,
        @@mouse_queued.y + ((event.y - last_y) * 2).to_i32
      )
    end
    @@last_mouse_x = event.x
    @@last_mouse_y = event.y

    if button = doom_button_from_ui(event.down)
      doom_button_down(button)
    end
    if button = doom_button_from_ui(event.up)
      doom_button_up(button)
    end
  end

  private def self.doom_button_from_ui(button : Int32) : CDoom::DoomButton?
    case button
    when 1 then CDoom::DoomButton::LEFT
    when 2 then CDoom::DoomButton::RIGHT
    when 3 then CDoom::DoomButton::MIDDLE
    else        nil
    end
  end

  private def self.release_ui_input
    @@keystates.each_with_index do |pressed, value|
      doom_key_up(CDoom::DoomKey.new(value)) if pressed
    end
    CDoom::DoomButton.each do |button|
      doom_button_up(button) if CDoom.button_states[button.value] != 0
    end
    @@mouse_queued = MouseDelta.new(0, 0)
    @@last_mouse_x = nil
    @@last_mouse_y = nil
  end

  def self.i_init_graphics
    CDoom.screens[0] = GC.malloc(CDoom::SCREENWIDTH * CDoom::SCREENHEIGHT).as(UInt8*)
    CDoom.screens[0].clear(CDoom::SCREENWIDTH * CDoom::SCREENHEIGHT)

    UIng.init
    @@ui_initialized = true
    @@closing = false

    handler = UIng::Area::Handler.new
    handler.draw do |_area, params|
      context = params.context
      black = UIng::Area::Draw::Brush.new(:solid, 0.0, 0.0, 0.0, 1.0)
      context.fill_path(black) do |path|
        path.add_rectangle(0, 0, params.area_width, params.area_height)
      end

      @@screen_image.try do |image|
        scale = {params.area_width / SRES_X, params.area_height / SRES_Y}.min
        width = SRES_X * scale
        height = SRES_Y * scale
        x = (params.area_width - width) / 2.0
        y = (params.area_height - height) / 2.0
        context.draw_image(image, x, y, width, height)
      end
    end
    handler.key_event do |_area, event|
      handle_ui_key(event)
      true
    end
    handler.mouse_event { |_area, event| handle_ui_mouse(event) }
    handler.mouse_crossed do |_area, _left|
      @@last_mouse_x = nil
      @@last_mouse_y = nil
    end
    handler.drag_broken do |_area|
      CDoom::DoomButton.each do |button|
        doom_button_up(button) if CDoom.button_states[button.value] != 0
      end
    end

    area = UIng::Area.new(handler)
    layout = UIng::Box.new(:vertical, padded: false)
    layout.append(area, stretchy: true)
    window = UIng::Window.new("Doo-cr", 1024, 768)
    window.on_closing do
      @@closing = true
      UIng.quit
      true
    end
    window.on_focus_changed { |focused| release_ui_input unless focused }
    window.set_child(layout)
    window.fullscreen = true if @@rlfullscreen != 0
    window.show

    @@ui_handler = handler
    @@ui_area = area
    @@ui_window = window
    UIng.on_should_quit do
      @@closing = true
      UIng.quit
      true
    end
    UIng.main_steps
  end

  def self.m_toggle_fullscreen(choice : Int32)
    @@rlfullscreen = 1 - @@rlfullscreen
    @@ui_window.try { |window| window.fullscreen = @@rlfullscreen != 0 }
  end
end
