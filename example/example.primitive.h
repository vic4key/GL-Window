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
    // text

    glColor3d(1., 1., 1.);
    renderer().text().render_text("these are primitives\na set of drawing functions", p2d(0., 0.85));

    // circle

    glColor3d(0., 1., 1.);
    renderer().circle(p2d(-0.3, 0.), 0.2, GLPrimitive::circle_t::solid);

    glColor3d(1., 1., 0.);
    renderer().circle(p2d(+0.3, 0.), 0.2, GLPrimitive::circle_t::fill);

    const auto& win = viewport().coordinate().win;

    glColor3d(1., 1., 0.);
    renderer().circle(win.center(), win.low() / 3, GLPrimitive::circle_t::stipple);

    // line

    glLineWidth(1);
    glColor3d(0., 1., 0.);
    renderer().line(p2i(50, 50), p2i(win.width() - 50, 50), GLPrimitive::line_t::dashdot);

    glLineWidth(3);
    glColor3d(1., 0., 1.);
    renderer().line(p2d(0., +0.5), p2d(0., -0.5), GLPrimitive::line_t::solid);

    // scatter

    glPointSize(5);
    glColor3d(0., 0., 1.);
    renderer().scatter({p2d(-0.2, -0.6), p2d(-0.1, -0.6), p2d(0.0, -0.6), p2d(+0.1, -0.6), p2d(+0.2, -0.6)});

    glPointSize(5);
    glColor3d(1., 0., 0.);
    renderer().scatter({p2i(200, 70), p2i(225, 70), p2i(250, 70), p2i(275, 70), p2i(300, 70)});
  }
};