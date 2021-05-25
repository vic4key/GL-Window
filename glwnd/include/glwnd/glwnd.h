#pragma once

/**
 * @file   glwnd.h
 * @author Vic P.
 * @brief  GL Window
 */

#include <string>
#include <vector>

#include "types.h"

struct GLFWwindow;

namespace glwnd
{

const color_t COLOR_BLACK = 0xFF000000;
const color_t COLOR_WHITE = 0xFFFFFFFF;
const color_t COLOR_GRAY  = 0xFF303030;

class GLViewPort;
class GLPrimitive;

class GLWindow
{
public:
  GLWindow(const std::string& name = "GL Window", int width = 500, int height = 500, color_t bg = COLOR_GRAY);
  virtual ~GLWindow();

  virtual void initial();
  virtual void final();

  virtual void on_display();
  virtual void on_resize(int width, int height);

  virtual void on_mouse_move(double x, double y);
  virtual void on_mouse_enter_leave(bool entered, double x, double y);
  virtual void on_mouse_click(int button, int action, int mods);
  virtual void on_mouse_wheel(double delta_x, double delta_y);

  virtual void on_keyboard_key(int key, int code, int action, int mods);
  virtual void on_keyboard_char(unsigned int code);

  virtual void on_drag_drop(const std::vector<std::string>& paths);

public:
  void run();
  void clear(color_t* pbg = nullptr);

  void enable_fps(bool state = true);
  void enable_debug(bool state = true);
  void enable_coordiates(bool state = true);

public:
  struct imgui_cfg
  {
    enum class styles
    {
      IMGUI_DARK,
      IMGUI_CLASSIC,
      IMGUI_LIGHT,
    } style = styles::IMGUI_CLASSIC;
    std::string font_path = "";
    float font_size = 0.F;
  };

  void enable_imgui(bool state, imgui_cfg* ptr_imgui_cfg = nullptr);

public:
  GLFWwindow& window();
  GLViewPort& viewport();
  GLPrimitive& renderer();

  const std::vector<std::string>& extensions() const;
  const std::vector<std::string>& arb_extensions() const;

private:
  class Impl;
  Impl* m_ptr_impl;
};

#define glwnd_3rd_stringize_ex(s) #s
#define glwnd_3rd_stringize(s) glwnd_3rd_stringize_ex(s)
#define glwnd_3rd_include(s)   glwnd_3rd_stringize(../3rdparty/s)

}; // glwnd