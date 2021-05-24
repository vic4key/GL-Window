#pragma once

/**
 * @file   viewport.h
 * @author Vic P.
 * @brief  GL View Port
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
    r4i win; // window coordinate - full view port (pixel on device screen)
    r4i squ; // square coordinate - center view port (as/is and relative to window coordinate)
    r4d ndc; // normalized device coordinate - center view port (normalized axises into [-1, +1])
  };

  GLViewPort(GLWindow& parent);
  virtual ~GLViewPort();

  void setup(int width, int height);

  coordinate_t& coordinate();

  p2d win_to_ndc(const p2i& point);
  p3d win_to_ndc(const p3i& point);

  p3i ndc_to_win(const p3d& point);
  p2i ndc_to_win(const p2d& point);

  void display_coordiates();

private:
  GLWindow& m_parent;
  coordinate_t m_coordinate;
};

}; // glwnd