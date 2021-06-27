#pragma once

#include "example.h"

#include <glwnd/text.h>

class GLViewExampleText2D : public GLView
{
public:
  GLViewExampleText2D()
    : GLView()
    , m_font_id_Georgia(INVALID_FONT_ID)
    , m_font_id_Trebuchet_MS(INVALID_FONT_ID) {}

  virtual ~GLViewExampleText2D() {}

  virtual void initial()
  {
    this->enable_coordiates();
    // m_text_render_2d.initialize(this);
    m_font_id_Georgia = m_text_render_2d.add_font("C:\\Windows\\Fonts\\courbd.ttf", 24);
    m_font_id_Trebuchet_MS = m_text_render_2d.add_font("C:\\Windows\\Fonts\\trebucbd.ttf", 32);
  }

  virtual void on_display()
  {
    //glColor3f(1.F, 1.F, 1.F);
    //m_text_render_2d.render_text("this is a text renderer\nsupported multi-lines\nsupported multi-fonts\n...", p2d(-0.75, +0.75));

    glColor3f(0.F, 1.F, 0.F);
    this->text().render_text("Courier New", p2d(0., 0.));

    //glColor3f(1.F, 0.F, 0.F);
    //m_text_render_2d.render_text("Georgia", p2i(50, 50), &m_font_id_Georgia);

    //glColor3f(0.F, 0.F, 1.F);
    //m_text_render_2d.render_text("Trebuchet MS", p2i(50, 100), &m_font_id_Trebuchet_MS);
  }

private:
  int m_font_id_Georgia;
  int m_font_id_Trebuchet_MS;
  TextRender2D m_text_render_2d;
};