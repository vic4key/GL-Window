/**
 * @file   viewport.cpp
 * @author Vic P.
 * @brief  GL View Port
 */

#include "glwnd/viewport.h"
#include "glwnd/glwnd.h"
#include <glwnd/utils.h>

#include <gl/glew.h>

namespace glwnd
{

GLViewPort::GLViewPort(GLWindow& parent) : m_parent(parent)
{
}

GLViewPort::~GLViewPort()
{
}

GLViewPort::coordinate_t& GLViewPort::coordinate()
{
  return m_coordinate;
}

void GLViewPort::setup(const r4i& rect)
{
  auto& win = m_coordinate.win;
  auto& ndc = m_coordinate.ndc;
  auto& squ = m_coordinate.squ;

  // change the current context matrix to projection

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // setup the window coordinate

  win.set(rect);
  win.flip(r4i::flip_t::vertical); // window coordinate -> opengl coordinate

  // setup the square coordinate

  const int square_size = win.low();
  squ.set(win);

  if (win.width() >= win.height())
  {
    int padding = (win.width() - square_size) / 2;
    squ.left(squ.left() + padding);
    squ.right(squ.right() - padding);
  }
  else
  {
    int padding = (win.height() - square_size) / 2;
    squ.top(squ.top() - padding);
    squ.bottom(squ.bottom() + padding);
  }

  // setup the normalized device coordinate

  const GLdouble aspect = win.aspect();

  ndc.set(-1.0, +1.0, +1.0, -1.0);

  if (win.width() >= win.height())
  {
    ndc.left(ndc.left() * aspect);
    ndc.right(ndc.right() * aspect);
  }
  else
  {
    ndc.top(ndc.top() / aspect);
    ndc.bottom(ndc.bottom() / aspect);
  }

  // setup view port - mapping window coordinate (win-flipped) to normalized device coordinate (ndc)

  glViewport(win.left(), win.bottom(), win.width(), win.height());
  gluOrtho2D(ndc.left(), ndc.right(), ndc.bottom(), ndc.top());

  // change the current context matrix to model-view

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

p3d GLViewPort::win_to_ndc(const p3i& point)
{
  auto& ndc = m_coordinate.ndc;
  auto& win = m_coordinate.win;

  auto x = utils::conv_range<GLdouble>(win.left(), win.right(), ndc.left(), ndc.right(), point.x());
  auto y = utils::conv_range<GLdouble>(win.bottom(), win.top(), ndc.bottom(), ndc.top(), point.y());
  auto z = 0.;

  return p3d(x, y, z);
}

p2d GLViewPort::win_to_ndc(const p2i& point)
{
  p3i p(point.x(), point.y(), 0);
  auto v = this->win_to_ndc(p);
  return p2d(v.x(), v.y());
}

p3i GLViewPort::ndc_to_win(const p3d& point)
{
  auto& ndc = m_coordinate.ndc;
  auto& win = m_coordinate.win;

  auto x = utils::conv_range<GLdouble>(ndc.left(), ndc.right(), win.left(), win.right(), point.x());
  auto y = utils::conv_range<GLdouble>(ndc.bottom(), ndc.top(), win.bottom(), win.top(), point.y());
  auto z = 0.;

  return p3i(int(x), int(y), int(z));
}

p2i GLViewPort::ndc_to_win(const p2d& point)
{
  p3d p(point.x(), point.y(), 0);
  auto v = this->ndc_to_win(p);
  return p2i(v.x(), v.y());
}

void GLViewPort::display_coordiates()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  const auto auto_fn_draw_coordinate = [&](const r4i& rect, const glcolorf& color) -> void
  {
    int r = rect.right();
    int t = rect.top();
    int l = rect.left();
    int b = rect.bottom();

    l += 1;
    t -= 1;

    p2d v;
    p2i p;

    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_LINES);
    {
      // for X

      // left bottom
      p.set(l, b);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // right top
      p.set(r, t);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // left top
      p.set(l, t);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // right bottom
      p.set(r, b);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // for +

      // left bottom
      p.set(l, b);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // right bottom
      p.set(r, b);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // left top
      p.set(l, t);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // right top
      p.set(r, t);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // left bottom
      p.set(l, b);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // left top
      p.set(l, t);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // right bottom
      p.set(r, b);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());

      // right top
      p.set(r, t);
      v = this->win_to_ndc(p);
      glVertex2d(v.x(), v.y());
    }
    glEnd();
  };

  // draw square/ndc coordinate

  auto_fn_draw_coordinate(m_coordinate.squ, glcolorf(1., 0., 1.));

  // draw window coordinate

  auto_fn_draw_coordinate(m_coordinate.win, glcolorf(1., 0., 0.));

  // draw center point of coordinates

  glColor3f(0.F, 1.F, 0.F);
  glBegin(GL_LINES);
  {
    glVertex2f(-0.1F, +0.0F);
    glVertex2f(+0.1F, +0.0F);
    glVertex2f(+0.F, -0.1F);
    glVertex2f(+0.F, +0.1F);
  }
  glEnd();

  glPopAttrib();
}

}; // glwnd