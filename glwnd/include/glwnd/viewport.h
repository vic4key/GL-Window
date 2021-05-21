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
public:
  struct coordinate_t
  {
    r4i win;
    r4d ndc;
  };

  GLViewPort(GLWindow& parent);
  virtual ~GLViewPort();

  coordinate_t& coordinate();

  void setup(int width, int height);

private:
  GLWindow& m_parent;
  coordinate_t m_coordinate;
};

}; // glwnd