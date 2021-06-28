#pragma once

/**
 * @file   fps.h
 * @author Vic P.
 * @brief  Frames Per Second (FPS)
 */

#include <chrono>

namespace glwnd
{

class GLView;

class FPS
{
public:
  FPS(GLView* ptr_view);
  virtual ~FPS();
  void render();

private:
  GLView& m_view;
  int m_fps, m_fps_counter;
  std::chrono::steady_clock::time_point m_start_time;
};

}; // glwnd