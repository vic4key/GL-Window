#pragma once

#include "example.h"

#include <glwnd/vbo.h>

class GLWindowExampleVBO : public GLWindow
{
public:
  GLWindowExampleVBO() : GLWindow() {};
  virtual ~GLWindowExampleVBO() {};

  virtual void on_display()
  {
    glColor3f(0.0, 1.0, 0.0);

    float vertices[] =
    {
      /*vertex*/ +0.0F, +0.5F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
      /*vertex*/ -0.5F, +0.2F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
      /*vertex*/ -0.5F, -0.2F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
      /*vertex*/ +0.0F, -0.5F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
      /*vertex*/ +0.0F, +0.5F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
      /*vertex*/ +0.5F, +0.2F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
      /*vertex*/ +0.5F, -0.2F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
      /*vertex*/ +0.0F, -0.5F, +0.0F, /*unused*/ 1.0F, 1.0F, 1.0F,
    };

    VBO vbo(vertices, sizeof(vertices), 6 * sizeof(vertices[0]));
    vbo.declare_data_format(0, 3, GL_FLOAT);
    vbo.draw(GL_POLYGON);
  }
};