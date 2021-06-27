#pragma once

#include "example.h"

class GLViewExampleSimple : public GLView
{
public:
  GLViewExampleSimple() : GLView() {}
  virtual ~GLViewExampleSimple() {}

  virtual void on_display()
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