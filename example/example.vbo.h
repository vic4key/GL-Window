#pragma once

#include "example.h"

#include <glwnd/vbo.h>

class GLViewExampleVBO : public GLView
{
public:
  GLViewExampleVBO() : GLView() {}
  virtual ~GLViewExampleVBO() {}

  virtual void on_display()
  {
    // With VBO - Eg. Format: |P|P|...|C|C|

    static GLfloat positions[] =
    {
      -1.0F, +1.0F,
      -0.5F, +1.0F,
      -1.0F, -1.0F,
    
      -1.0F, -1.0F,
      -0.5F, +1.0F,
      +0.5F, -1.0F,
    
      +0.5F, -1.0F,
      -0.5F, +1.0F,
      +1.0F, +1.0F,
    
      +1.0F, +1.0F,
      +0.5F, -1.0F,
      +1.0F, -1.0F,
    };

    static GLfloat colors[] =
    {
      1.0F, 0.0F, 0.0F,
      1.0F, 0.0F, 0.0F,
      1.0F, 0.0F, 0.0F,
    
      0.0F, 1.0F, 0.0F,
      0.0F, 1.0F, 0.0F,
      0.0F, 1.0F, 0.0F,
    
      0.0F, 0.0F, 1.0F,
      0.0F, 0.0F, 1.0F,
      0.0F, 0.0F, 1.0F,
    
      1.0F, 0.0F, 1.0F,
      1.0F, 0.0F, 1.0F,
      1.0F, 0.0F, 1.0F,
    };

    // GLuint vds_size = (2 + 3) * sizeof(GLfloat); // this vds has 2 attributes (position 2f + color 3f = 5f)
    // VBO vbo;
    // vbo.setup_begin({ {positions, sizeof(positions)}, {colors, sizeof(colors)} }, vds_size);
    // {
    //   GLuint offset = 0;
    //   vbo.declare_position_format(offset, 2, GL_FLOAT);
    // 
    //   offset = sizeof(positions);
    //   vbo.declare_color_format(offset, 3, GL_FLOAT);
    // }
    // vbo.setup_end();
    // vbo.render(GL_TRIANGLES);

    // With VBO - Eg. Format: |P|C|...|P|C|

    static GLfloat data[] =
    {
      -1.0F, +1.0F,
      1.0F, 0.0F, 0.0F,

      -0.5F, +1.0F,
      1.0F, 0.0F, 0.0F,

      -1.0F, -1.0F,
      1.0F, 0.0F, 0.0F,

      -1.0F, -1.0F,
      0.0F, 1.0F, 0.0F,

      -0.5F, +1.0F,
      0.0F, 1.0F, 0.0F,

      +0.5F, -1.0F,
      0.0F, 1.0F, 0.0F,

      +0.5F, -1.0F,
      0.0F, 0.0F, 1.0F,

      -0.5F, +1.0F,
      0.0F, 0.0F, 1.0F,

      +1.0F, +1.0F,
      0.0F, 0.0F, 1.0F,

      +1.0F, +1.0F,
      1.0F, 0.0F, 1.0F,

      +0.5F, -1.0F,
      1.0F, 0.0F, 1.0F,

      +1.0F, -1.0F,
      1.0F, 0.0F, 1.0F,
    };

    // GLuint vds_size = (2 + 3) * sizeof(GLfloat); // this vds has 2 attributes (position 2f + color 3f = 5f)
    // VBO vbo;
    // vbo.setup_begin(&data, sizeof(data), vds_size);
    // {
    //   GLuint offset = 0;
    //   vbo.declare_position_format(0, 2, GL_FLOAT, vds_size);
    // 
    //   offset = 2 * sizeof(GLfloat);
    //   vbo.declare_color_format(offset, 3, GL_FLOAT, vds_size);
    // }
    // vbo.setup_end();
    // vbo.render(GL_TRIANGLES);

    // Without VBO

    glBegin(GL_TRIANGLES);
    {
      glColor3f(1.0F, 0.0F, 0.0F);
      glVertex2f(-1.0F, +1.0F);
      glVertex2f(-0.5F, +1.0F);
      glVertex2f(-1.0F, -1.0F);

      glColor3f(0.0F, 1.0F, 0.0F);
      glVertex2f(-1.0F, -1.0F);
      glVertex2f(-0.5F, +1.0F);
      glVertex2f(+0.5F, -1.0F);

      glColor3f(0.0F, 0.0F, 1.0F);
      glVertex2f(+0.5F, -1.0F);
      glVertex2f(-0.5F, +1.0F);
      glVertex2f(+1.0F, +1.0F);

      glColor3f(1.0F, 0.0F, 1.0F);
      glVertex2f(+1.0F, +1.0F);
      glVertex2f(+0.5F, -1.0F);
      glVertex2f(+1.0F, -1.0F);
    }
    glEnd();
  }
};