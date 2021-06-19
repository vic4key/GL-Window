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
    glBegin(GL_POLYGON);
    {
      glVertex3f(+0.0F, +0.5F, +0.0F);
      glVertex3f(-0.5F, +0.2F, +0.0F);
      glVertex3f(-0.5F, -0.2F, +0.0F);
      glVertex3f(+0.0F, -0.5F, +0.0F);
      glVertex3f(+0.0F, +0.5F, +0.0F);
      glVertex3f(+0.5F, +0.2F, +0.0F);
      glVertex3f(+0.5F, -0.2F, +0.0F);
      glVertex3f(+0.0F, -0.5F, +0.0F);
    }
    glEnd();
  }
};