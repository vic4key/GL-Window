/**
 * @file   viewport.cpp
 * @author Vic P.
 * @brief  GL ViewPort
 */

#include "glwnd/viewport.h"
#include "glwnd/glwnd.h"
#include <glwnd/utils.h>

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

void GLViewPort::setup(int width, int height)
{
  auto& win = m_coordinate.win;
  auto& ndc = m_coordinate.ndc;
  auto& squ = m_coordinate.squ;

  // change the current context matrix to projection

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // calculate the aspect value

  width  = width  == 0 ? 1 : width;
  height = height == 0 ? 1 : height;
  const GLdouble aspect = GLdouble(width) / GLdouble(height);

  // setup the window coordinate

  win.set(0, 0, width, height);
  win.flip(r4i::flip_t::vertical); // win coordinate -> ndc coordinate

  glViewport(0, 0, win.width(), win.height());

  // setup the square coordinate

  const int square_size = aspect > 1. ? win.height() : win.width();
  squ.set(win.width(), win.height());
  squ.flip(r4i::flip_t::vertical); // square coordinate -> ndc coordinate

  if (win.width() >= win.height())
  {
    int padding = (win.width() - square_size) / 2;
    squ.left(padding);
    squ.right(square_size + padding);
  }
  else
  {
    int padding = (win.height() - square_size) / 2;
    squ.top(square_size + padding);
    squ.bottom(padding);
  }

  // setup the normalized device coordinate

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

  gluOrtho2D(ndc.left(), ndc.right(), ndc.bottom(), ndc.top());

  // change the current context matrix to model-view

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

p3d GLViewPort::win_to_ndc(const p3i& point)
{
  auto& ndc = m_coordinate.ndc;
  auto& win = m_coordinate.win;

  auto x = conv_range<GLdouble>(0, win.width(), ndc.left(), ndc.right(), point.x());
  auto y = conv_range<GLdouble>(0, win.height(), ndc.bottom(), ndc.top(), point.y());
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

  auto x = conv_range<GLdouble>(ndc.left(), ndc.right(), 0, win.width(), point.x());
  auto y = conv_range<GLdouble>(ndc.bottom(), ndc.top(), 0, win.height(), point.y());
  auto z = 0.;

  return p3i(int(x), int(y), int(z));
}

p2i GLViewPort::ndc_to_win(const p2d& point)
{
  p3d p(point.x(), point.y(), 0);
  auto v = this->ndc_to_win(p);
  return p2i(v.x(), v.y());
}

}; // glwnd