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

    GLfloat data[] =
    {
      /*position*/ -1.0F, +1.0F, /*color*/ 1.0F, 0.0F, 0.0F,
      /*position*/ -0.5F, +1.0F, /*color*/ 1.0F, 0.0F, 0.0F,
      /*position*/ -1.0F, -1.0F, /*color*/ 1.0F, 0.0F, 0.0F,

      /*position*/ -1.0F, -1.0F, /*color*/ 0.0F, 1.0F, 0.0F,
      /*position*/ -0.5F, +1.0F, /*color*/ 0.0F, 1.0F, 0.0F,
      /*position*/ +0.5F, -1.0F, /*color*/ 0.0F, 1.0F, 0.0F,

      /*position*/ +0.5F, -1.0F, /*color*/ 0.0F, 0.0F, 1.0F,
      /*position*/ -0.5F, +1.0F, /*color*/ 0.0F, 0.0F, 1.0F,
      /*position*/ +1.0F, +1.0F, /*color*/ 0.0F, 0.0F, 1.0F,

      /*position*/ +1.0F, +1.0F, /*color*/ 1.0F, 0.0F, 1.0F,
      /*position*/ +0.5F, -1.0F, /*color*/ 1.0F, 0.0F, 1.0F,
      /*position*/ +1.0F, -1.0F, /*color*/ 1.0F, 0.0F, 1.0F,
    };

    GLuint offset = 0;
    GLuint vds_size = 5 * sizeof(GLfloat); // this vds has 2 attributes (position 2f + color 3f = 5f)
    VBO vbo(data, sizeof(data), vds_size);
    offset = vbo.declare_position_format(offset, 2, GL_FLOAT, vds_size); // position -> 2f
    offset = vbo.declare_color_format(offset, 3, GL_FLOAT, vds_size);    // color    -> 3f
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