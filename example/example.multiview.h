#pragma once

#include "example.h"

#include <glwnd/view.h>
#include <glwnd/layout.h>

class GLViewExampleMultiView : public GLView
{
public:
  GLViewExampleMultiView() : GLView() {};
  virtual ~GLViewExampleMultiView() {};

  virtual void on_display()
  {
    color_t colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFF00FF };
    auto color = glcolor_t<GLfloat>(colors[this->index()]);

    glColor3f(color.r, color.g, color.b);

    switch (this->index())
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
        this->circle(p2d(0., 0.), 0.5, GLPrimitive::circle_t::fill);
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