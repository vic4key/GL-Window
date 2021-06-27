#pragma once

#include "example.h"

#include <glwnd/tex2d.h>

class GLViewExampleImage : public GLView
{
public:
  GLViewExampleImage() : GLView() {}
  virtual ~GLViewExampleImage() {}

  virtual void initial()
  {
    m_tex2d.initialize_from_image_file("assets\\example.png");
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
  Tex2D m_tex2d;
};