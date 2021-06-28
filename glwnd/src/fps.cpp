/**
 * @file   fps.cpp
 * @author Vic P.
 * @brief  Frames Per Second (FPS)
 */

#include "fps.h"

#include "glwnd/view.h"
#include "glwnd/text.h"

#include <windows.h>

namespace glwnd
{

FPS::FPS(GLView* ptr_view) : m_view(*ptr_view), m_fps(0), m_fps_counter(0)
{
  m_start_time = std::chrono::high_resolution_clock::now();
}

FPS::~FPS()
{
}

void FPS::render()
{
  m_fps_counter += 1;

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> delta_time = end_time - m_start_time;

  if (delta_time.count() > 1000.0) // 1000ms
  {
    m_fps = m_fps_counter;
    m_fps_counter = 0;
    m_start_time = std::chrono::high_resolution_clock::now();
  }

  static char fps_text[MAXBYTE] = { 0 };
  sprintf_s(fps_text, "FPS : %d\0", m_fps);

  // const int text_padding = 10;
  // const int text_height  = 15;
  // const auto& win = m_view.viewport().coordinate().win;
  // const p2i point(text_padding, win.top() - text_height - text_padding);
  const p2d point(-0.9, +0.8);
  m_view.text().render_text(fps_text, point);
}

}; // glwnd