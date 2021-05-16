#pragma once

#include "example.h"

#include <glwnd/vbo.h>

class GLWindowExampleVBO : public GLWindow
{
public:
  GLWindowExampleVBO() : GLWindow() {}
  virtual ~GLWindowExampleVBO() {}

  virtual void on_display()
  {
    // With VBO

    float data[] =
    {
      /*vertex*/ -1.0F, +1.0F, /*color*/ 1.0F, 0.0F, 0.0F,
      /*vertex*/ -0.5F, +1.0F, /*color*/ 1.0F, 0.0F, 0.0F,
      /*vertex*/ -1.0F, -1.0F, /*color*/ 1.0F, 0.0F, 0.0F,

      /*vertex*/ -1.0F, -1.0F, /*color*/ 0.0F, 1.0F, 0.0F,
      /*vertex*/ -0.5F, +1.0F, /*color*/ 0.0F, 1.0F, 0.0F,
      /*vertex*/ +0.5F, -1.0F, /*color*/ 0.0F, 1.0F, 0.0F,

      /*vertex*/ +0.5F, -1.0F, /*color*/ 0.0F, 0.0F, 1.0F,
      /*vertex*/ -0.5F, +1.0F, /*color*/ 0.0F, 0.0F, 1.0F,
      /*vertex*/ +1.0F, +1.0F, /*color*/ 0.0F, 0.0F, 1.0F,

      /*vertex*/ +1.0F, +1.0F, /*color*/ 1.0F, 0.0F, 1.0F,
      /*vertex*/ +0.5F, -1.0F, /*color*/ 1.0F, 0.0F, 1.0F,
      /*vertex*/ +1.0F, -1.0F, /*color*/ 1.0F, 0.0F, 1.0F,
    };

    GLuint next_offset = 0;
    VBO vbo(data, sizeof(data), 5 * sizeof(float)); // 1 group (vertex 2f, color 3f) = 5f elements
    vbo.declare_vertex_format(next_offset, 2, GL_FLOAT, &next_offset); // vertex -> 2f
    vbo.declare_color_format (next_offset, 3, GL_FLOAT, &next_offset); // color  -> 3f
    vbo.draw(GL_TRIANGLES);

    // Without VBO

    // glBegin(GL_TRIANGLES);
    // {
    //   glColor3f(1.0F, 0.0F, 0.0F);
    //   glVertex2f(-1.0F, +1.0F);
    //   glVertex2f(-0.5F, +1.0F);
    //   glVertex2f(-1.0F, -1.0F);
    // 
    //   glColor3f(0.0F, 1.0F, 0.0F);
    //   glVertex2f(-1.0F, -1.0F);
    //   glVertex2f(-0.5F, +1.0F);
    //   glVertex2f(+0.5F, -1.0F);
    // 
    //   glColor3f(0.0F, 0.0F, 1.0F);
    //   glVertex2f(+0.5F, -1.0F);
    //   glVertex2f(-0.5F, +1.0F);
    //   glVertex2f(+1.0F, +1.0F);
    // 
    //   glColor3f(1.0F, 0.0F, 1.0F);
    //   glVertex2f(+1.0F, +1.0F);
    //   glVertex2f(+0.5F, -1.0F);
    //   glVertex2f(+1.0F, -1.0F);
    // }
    // glEnd();
  }
};