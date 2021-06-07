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

    GLfloat positions[] =
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
    
    GLfloat colors[] =
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
    
    VBO vbo;
    GLuint vds_size = 5 * sizeof(GLfloat); // this vds has 2 attributes (position 2f + color 3f = 5f)
    vbo.initialize({{positions, sizeof(positions)}, {colors, sizeof(colors)}}, vds_size);

    GLuint offset = 0;
    vbo.declare_position_format(offset, 2, GL_FLOAT, 0);

    offset = sizeof(positions);
    vbo.declare_color_format(offset, 3, GL_FLOAT, 0);

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