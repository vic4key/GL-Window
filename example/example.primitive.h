#pragma once

#include "example.h"

#include <glwnd/primitive.h>
#include <glwnd/viewport.h>

class GLWindowExamplePrimitive : public GLWindow
{
public:
  GLWindowExamplePrimitive() : GLWindow() {}
  virtual ~GLWindowExamplePrimitive() {}

  virtual void on_display()
  {
    glColor3d(1., 1., 1.);
    renderer().text().render_text("these are primitives\na set of drawing functions", p2d(0., 0.85));

    glColor3d(0., 1., 1.);
    renderer().circle(p2d(-0.3, 0.), 0.2, false); // no-fill

    glColor3d(1., 1., 0.);
    renderer().circle(p2d(+0.3, 0.), 0.2, true); // fill-ed

    const auto& win = viewport().coordinate().win;

    glColor3d(1., 1., 0.);
    renderer().circle(win.center(), win.low() / 3);

    glLineWidth(5);
    glColor3d(1., 0., 1.);
    renderer().line(p2d(0., +0.5), p2d(0., -0.5));

    glLineWidth(7);
    glColor3d(0., 1., 0.);
    renderer().line(p2i(50, 50), p2i(win.width() - 50, 50));
  }
};