#pragma once

/**
 * @file   viewport.h
 * @author Vic P.
 * @brief  GL ViewPort
 */

#include <gl/glew.h>
#include <glwnd/geometry.h>

namespace glwnd
{

class GLWindow;

class GLViewPort
{
  friend GLWindow;

public:
  struct coordinate_t
  {
    rect_t<GLint> clip;
    rect_t<GLdouble> ndc;
  };

  GLViewPort(GLWindow* ptr_parent);
  virtual ~GLViewPort();

  coordinate_t& coordinate();

private:
  GLWindow* m_ptr_parent;
  coordinate_t m_coordinate;
};

}; // glwnd