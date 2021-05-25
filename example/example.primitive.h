#pragma once

#include "example.h"

#include <glwnd/primitive.h>

class GLWindowExamplePrimitive : public GLWindow
{
public:
  GLWindowExamplePrimitive() : GLWindow() {}
  virtual ~GLWindowExamplePrimitive() {}

  virtual void on_display()
  {
    glColor3d(0., 1., 1.);
    renderer().circle(p2d(-0.3, 0.), 0.2);

    glColor3d(1., 1., 0.);
    renderer().circle(p2d(+0.3, 0.), 0.2, true);

    glLineWidth(5);
    glColor3d(1., 0., 1.);
    renderer().line(p2d(0., +0.5), p2d(0., -0.5));
  }
};