#pragma once

#include "example.h"

#include <glwnd/pbo.h>
#include <SOIL2/SOIL2>

class GLWindowExamplePBO : public GLWindow
{
public:
  GLWindowExamplePBO() : GLWindow() {}
  virtual ~GLWindowExamplePBO() {}

  virtual void initial()
  {
    m_ptr_image = SOIL_load_image("data\\example.png", &m_width, &m_height, &m_channel, SOIL_LOAD_RGBA);
    m_pbo.initialize(m_ptr_image, m_width, m_height, m_channel, GL_RGBA, GL_RGBA);
  }

  virtual void final()
  {
    SOIL_free_image_data(m_ptr_image);
  }

  virtual void on_display()
  {
    GLuint texture = 0;
    glGenTextures(1, &texture);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    m_pbo.use();

    glBegin(GL_QUADS);
    {
      glTexCoord2i(0, 1); glVertex2f(-1.F, -1.F); // left  bottom
      glTexCoord2i(1, 1); glVertex2f(+1.F, -1.F); // right bottom
      glTexCoord2i(1, 0); glVertex2f(+1.F, +1.F); // right top
      glTexCoord2i(0, 0); glVertex2f(-1.F, +1.F); // left  top
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glDeleteTextures(1, &texture);
  }

private:
  int m_width = 0, m_height = 0, m_channel = 0;
  unsigned char* m_ptr_image = nullptr;

  PBO m_pbo;
};