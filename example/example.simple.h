#pragma once

#include "example.h"

class GLWindowExampleSimple : public GLWindow
{
public:
  GLWindowExampleSimple() : GLWindow() {}
  virtual ~GLWindowExampleSimple() {}

  virtual void on_display(GLView& view)
  {
    glColor3f(0.0, 1.0, 0.0);
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