/**
 * @file   viewport.cpp
 * @author Vic P.
 * @brief  GL ViewPort
 */

#include "glwnd/viewport.h"
#include "glwnd/glwnd.h"

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

  // change the current context matrix to projection

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // setup the win coordinate (window coordinate on screen in pixel)

  width  = width  == 0 ? 1 : width;
  height = height == 0 ? 1 : height;
  win.set(0, 0, width, height);
  win.flip(r4i::flip_t::vertical); // win coordinate -> ndc coordinate

  glViewport(0, 0, win.width(), win.height());

  // setup the ndc coordinate (normalized device coordinate)

  const GLdouble aspect = GLdouble(win.width()) / GLdouble(win.height());

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

}; // glwnd