#pragma once

#include "example.vds.h"

#include <glfw/glfw3.h>

class GLWindowExampleInteractive : public GLWindowExampleVDS2A
{
public:
  GLWindowExampleInteractive() : GLWindowExampleVDS2A() {}
  virtual ~GLWindowExampleInteractive() {}

  virtual void on_display(GLView& view)
  {
    glMatrixMode(GL_PROJECTION_MATRIX);
    gluPerspective(45, 1.F, 0.1, 100);

    glMatrixMode(GL_MODELVIEW_MATRIX);
    glTranslatef(0, 0, -5);

    // rotate and scale cube
    // https://i.stack.imgur.com/1OFpX.png

    glRotated(m_rotate_factor.x(), 1, 0, 0); // pitch - rotate around x-axis
    glRotated(m_rotate_factor.y(), 0, 1, 0); // jaw   - rotate around y-axis
    glRotated(m_rotate_factor.z(), 0, 0, 1); // roll  - rotate around z-axis

    glScaled(m_scale_factor, m_scale_factor, m_scale_factor);

    // draw cube via vbo

    m_vbo.render(GL_QUADS);
  }

  virtual void on_mouse_move(int x, int y)
  {
    if (m_mouse_left_down)
    {
      auto v = v2i(x, y) - m_mouse_left_down_position;
      m_rotate_factor = v2i(-v.y(), v.x());
    }
  }

  virtual void on_mouse_click(int button, int action, int mods, int x, int y)
  {
    if (m_mouse_left_down = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
      m_mouse_left_down_position = v2i(x, y);
    }
  }

  virtual void on_mouse_wheel(int dx, int dy)
  {
    const std::pair<GLdouble, GLdouble> scale_limit(0.1, 2.0);
    const GLdouble scale_speed = 0.1;

    m_scale_factor += dy * scale_speed;

    if (m_scale_factor < scale_limit.first)
    {
      m_scale_factor = scale_limit.first;
    }
    else if (m_scale_factor > scale_limit.second)
    {
      m_scale_factor = scale_limit.second;
    }
  }

  virtual void on_keyboard_key(int key, int code, int action, int mods)
  {
    if (action == GLFW_PRESS && key == GLFW_KEY_F11)
    {
      this->toggle_fullscreen();
    }

    p2i v(0, 0);

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
      const int rotate_speed = 10;

      switch (key)
      {
      case GLFW_KEY_UP:
        v.x(v.x() + rotate_speed);
        break;

      case GLFW_KEY_DOWN:
        v.x(v.x() - rotate_speed);
        break;

      case GLFW_KEY_LEFT:
        v.y(v.y() - rotate_speed);
        break;

      case GLFW_KEY_RIGHT:
        v.y(v.y() + rotate_speed);
        break;

      default:
        break;
      }
    }

    m_rotate_factor += v2i(-v.x(), v.y());
  }

private:
  bool m_mouse_left_down = false;
  v2i  m_mouse_left_down_position;
  v2i  m_rotate_factor;

  GLdouble m_scale_factor = 1.;
};