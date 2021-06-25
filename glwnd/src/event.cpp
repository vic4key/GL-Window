/**
 * @file   event.cpp
 * @author Vic P.
 * @brief  GL Event
 */

#include "glwnd/event.h"

namespace glwnd
{

GLEvent::GLEvent()
{
}

GLEvent::~GLEvent()
{
}

void GLEvent::initial()
{
  // OVERRIDABLE
}

void GLEvent::final()
{
  // OVERRIDABLE
}

void GLEvent::on_display(GLView& view)
{
  // OVERRIDABLE
}

void GLEvent::on_resize(int width, int height)
{
  // OVERRIDABLE
}

void GLEvent::on_mouse_move(int x, int y)
{
  // OVERRIDABLE
}

void GLEvent::on_mouse_enter_leave(bool entered, int x, int y)
{
  // OVERRIDABLE
}

void GLEvent::on_mouse_click(int button, int action, int mods, int x, int y)
{
  // OVERRIDABLE
}

void GLEvent::on_mouse_wheel(int dx, int dy)
{
  // OVERRIDABLE
}

void GLEvent::on_keyboard_key(int key, int code, int action, int mods)
{
  // OVERRIDABLE
}

void GLEvent::on_keyboard_char(unsigned int code)
{
  // OVERRIDABLE
}

void GLEvent::on_drag_drop(const std::vector<std::string>& paths)
{
  // OVERRIDABLE
}

}; // glwnd