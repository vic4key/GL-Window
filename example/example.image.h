#pragma once

#include "example.h"

#include <SOIL2/SOIL2>

class GLWindowExampleImage : public GLWindow
{
public:
  GLWindowExampleImage() : GLWindow() {}
  virtual ~GLWindowExampleImage() {}

  virtual void initial()
  {
    m_ptr_image = SOIL_load_image("data\\example.png", &m_width, &m_height, 0, SOIL_LOAD_RGBA);
  }

  virtual void final()
  {
    SOIL_free_image_data(m_ptr_image);
  }

  virtual void on_display()
  {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ptr_image);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

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
  int m_width = 0, m_height = 0;
  unsigned char* m_ptr_image = nullptr;
};