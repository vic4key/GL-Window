#pragma once

#include "example.h"

#include <glwnd/tex2d.h>

class GLWindowExampleImage : public GLWindow
{
public:
  GLWindowExampleImage() : GLWindow() {}
  virtual ~GLWindowExampleImage() {}

  virtual void initial()
  {
    m_tex2d.init_from_image_file("data\\example.png");
  }

  virtual void on_display()
  {
    glEnable(GL_TEXTURE_2D);

    m_tex2d.use();

    glBegin(GL_QUADS);
    {
      glTexCoord2i(0, 1); glVertex2f(-1.F, -1.F); // left  bottom
      glTexCoord2i(1, 1); glVertex2f(+1.F, -1.F); // right bottom
      glTexCoord2i(1, 0); glVertex2f(+1.F, +1.F); // right top
      glTexCoord2i(0, 0); glVertex2f(-1.F, +1.F); // left  top
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
  }

private:
  glwnd::Tex2D m_tex2d;
};