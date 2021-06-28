#pragma once

/**
 * @file   viewport.h
 * @author Vic P.
 * @brief  GL View Port
 */

#include <glwnd/geometry.h>

namespace glwnd
{

class GLView;
class GLWindow;
class TextRender2D;

class GLViewPort
{
  friend GLWindow;
  friend TextRender2D;

public:
  struct coordinate_t
  {
    r4i win; // window coordinate - full view port (pixel on device screen)
    r4i squ; // square coordinate - center view port (as/is and relative to window coordinate)
    r4d ndc; // normalized device coordinate - center view port (normalized axises into [-1, +1])
  };

  GLViewPort();
  virtual ~GLViewPort();

  GLViewPort(const GLViewPort& right);
  GLViewPort& operator=(const GLViewPort& right);

  void setup(const r4i& rect);

  coordinate_t& coordinate();

  void display_coordiates();

  void set_ptr_view(GLView* ptr_view);
  GLView* get_ptr_view();

  p3i ndc_to_vpc(const p3d& point);
  p2i ndc_to_vpc(const p2d& point);
  p2d vpc_to_ndc(const p2i& point);
  p3d vpc_to_ndc(const p3i& point);

private:
  p2i vpc_to_win(const p2i& point);
  p3i vpc_to_win(const p3i& point);
  p2i win_to_vpc(const p2i& point);
  p3i win_to_vpc(const p3i& point);

  p2d win_to_ndc(const p2i& point);
  p3d win_to_ndc(const p3i& point);
  p3i ndc_to_win(const p3d& point);
  p2i ndc_to_win(const p2d& point);

private:
  GLView* m_ptr_view;
  coordinate_t m_coordinate;
};

}; // glwnd