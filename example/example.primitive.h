#pragma once

#include "example.h"

class GLViewExamplePrimitive : public GLView
{
public:
  GLViewExamplePrimitive() : GLView() {}
  virtual ~GLViewExamplePrimitive() {}

  virtual void on_display()
  {
    // text

    glColor3d(1., 1., 1.);
    this->text().render_text("these are primitives\na set of drawing functions", p2d(0., 0.85));

    // circle

    glColor3d(0., 1., 1.);
    this->circle(p2d(-0.3, 0.), 0.2, GLPrimitive::circle_t::solid);

    glColor3d(1., 1., 0.);
    this->circle(p2d(+0.3, 0.), 0.2, GLPrimitive::circle_t::fill);

    const auto& win = viewport().coordinate().win;

    glColor3d(1., 1., 0.);
    this->circle(p2d(0., 0.), .7, GLPrimitive::circle_t::stipple);

    // line

    glLineWidth(1);
    glColor3d(0., 1., 0.);
    this->line(p2i(50, 50), p2i(win.width() - 50, 50), GLPrimitive::line_t::dashdot);

    glLineWidth(3);
    glColor3d(1., 0., 1.);
    this->line(p2d(0., +0.5), p2d(0., -0.5), GLPrimitive::line_t::solid);

    // scatter

    glPointSize(5);
    glColor3d(0., 0., 1.);
    this->scatter({p2d(-0.2, -0.6), p2d(-0.1, -0.6), p2d(0.0, -0.6), p2d(+0.1, -0.6), p2d(+0.2, -0.6)});

    glPointSize(5);
    glColor3d(1., 0., 0.);
    this->scatter({p2i(200, 70), p2i(225, 70), p2i(250, 70), p2i(275, 70), p2i(300, 70)});
  }
};