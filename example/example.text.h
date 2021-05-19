#pragma once

#include "example.h"

#include <glwnd/text.h>

class GLWindowExampleText : public GLWindow
{
public:
  GLWindowExampleText() : GLWindow() {}
  virtual ~GLWindowExampleText() {}

  virtual void initial()
  {
    m_text_render.setup(this, "C:\\Windows\\Fonts\\cour.ttf", 72);
  }

  virtual void on_display()
  {
    m_text_render.draw(
      "hello world",
      0.F, 0.F,
      glwnd::glcolor_t<float>(0.F, 1.F, 0.F),
      TextRender::eTextAlignment::ALIGN_CENTER,
      TextRender::eTextAlignment::ALIGN_CENTER,
      3.F
    );
  }

private:
  TextRender m_text_render;
};