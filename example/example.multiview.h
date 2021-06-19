#pragma once

#include "example.h"

#include <glwnd/view.h>
#include <glwnd/layout.h>

class GLWindowExampleMultiView : public GLWindow
{
public:
  GLWindowExampleMultiView() : GLWindow() {}
  virtual ~GLWindowExampleMultiView() {}

  virtual void initial()
  {
    // this->set_layout(GLLayout::_1x1(*this));
    // this->set_layout(GLLayout::_1x2(*this));
    // this->set_layout(GLLayout::_2x1(*this));
    this->set_layout(GLLayout::_2x2(*this));
    this->enable_coordiates();
  }

  virtual void on_display(GLView& view)
  {
    color_t colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFF00FF };
    auto color = glcolor_t<GLfloat>(colors[view.index()]);

    glColor3f(color.r, color.g, color.b);

    switch (view.index())
    {
    case 0:
      {
        glBegin(GL_TRIANGLES);
        {
          glVertex2f(-0.5, 0.5);
          glVertex2f(-0.5, -0.5);
          glVertex2f(0.5, 0.5);
          glVertex2f(0.5, 0.5);
          glVertex2f(-0.5, -0.5);
          glVertex2f(0.5, -0.5);
        }
        glEnd();
      }
      break;

    case 1:
      {
        glBegin(GL_POLYGON);
        {
          glVertex2f(+0.0F, +0.5F);
          glVertex2f(-0.5F, +0.2F);
          glVertex2f(-0.5F, -0.2F);
          glVertex2f(+0.0F, -0.5F);
          glVertex2f(+0.0F, +0.5F);
          glVertex2f(+0.5F, +0.2F);
          glVertex2f(+0.5F, -0.2F);
          glVertex2f(+0.0F, -0.5F);
        }
        glEnd();
      }
      break;

    case 2:
      {
        renderer().circle(p2d(0., 0.), 0.5, GLPrimitive::circle_t::fill);
      }
      break;

    case 3:
      {
        glBegin(GL_TRIANGLES);
        {
          glVertex2f(-0.5F, -0.5F);
          glVertex2f(+0.5F, -0.5F);
          glVertex2f(+0.0F, +0.5F);
        }
        glEnd();
      }
      break;

    default:
      break;
    }
  }
};