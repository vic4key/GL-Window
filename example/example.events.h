#pragma once

#include "example.h"

#include <glwnd/utils.h>

class GLViewExampleEvents : public GLView
{
public:
  GLViewExampleEvents() : GLView() {};
  virtual ~GLViewExampleEvents() {};

  virtual void on_display()
  {
    LOG("drawing");
  }

  virtual void on_resize(int width, int height)
  {
    LOG("%d %d", width, height);
  }

  virtual void on_mouse_move(int x, int y)
  {
    LOG("%d %d", x, y);
  }

  virtual void on_mouse_enter_leave(bool entered, int x, int y)
  {
    LOG("%s %d %d", entered ? "enter" : "leave", x, y);
  }

  virtual void on_mouse_click(int button, int action, int mods, int x, int y)
  {
    LOG("%d %d %d %d %d", button, action, mods, x, y);
  }

  virtual void on_mouse_wheel(int dx, int dy)
  {
    LOG("%d %d", dx, dy);
  }

  virtual void on_keyboard_key(int key, int code, int action, int mods)
  {
    LOG("%c %d %d %d", char(key), code, action, mods);
  }

  virtual void on_keyboard_char(unsigned int code)
  {
    LOG("%d", code);
  }

  virtual void on_drag_drop(const std::vector<std::string>& paths)
  {
    LOG("%d", paths.size());
    for (auto& path : paths)
    {
      LOG("`%s`", path.c_str());
    }
  }
};