#pragma once

/**
 * @file   glwnd.h
 * @author Vic P.
 * @brief  GL Window
 */

#include "defs.h"

struct GLFWwindow;

namespace glwnd
{

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
  void enable_dear_imgui(bool state = true, dear_imgui_cfg* ptr_imgui_cfg = nullptr);

public:
  GLFWwindow&  window();
  GLViewPort&  viewport();
  GLPrimitive& renderer();

  const std::vector<std::string>& extensions() const;
  const std::vector<std::string>& arb_extensions() const;

private:
  class Impl;
  Impl* m_ptr_impl;
};

}; // glwnd