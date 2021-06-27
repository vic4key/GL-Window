#pragma once

/**
 * @file   event.h
 * @author Vic P.
 * @brief  GL Event
 */

#include <vector>
#include <string>

namespace glwnd
{

class GLEvent
{
public:
	GLEvent();
	virtual ~GLEvent();

  virtual void initial();
  virtual void final();

  virtual void on_display() = 0;
  virtual void on_resize(int width, int height);

  virtual void on_mouse_move(int x, int y);
  virtual void on_mouse_enter_leave(bool entered, int x, int y);
  virtual void on_mouse_click(int button, int action, int mods, int x, int y);
  virtual void on_mouse_wheel(int dx, int dy);

  virtual void on_keyboard_key(int key, int code, int action, int mods);
  virtual void on_keyboard_char(unsigned int code);

  virtual void on_drag_drop(const std::vector<std::string>& paths);
};

}; // glwnd