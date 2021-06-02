#pragma once

#include "example.h"

#include <glwnd/tex2d.h>
#include <glwnd/vbo.h>

class GLWindowExampleVDS : public GLWindow
{
public:
  GLWindowExampleVDS() : GLWindow() {}
  virtual ~GLWindowExampleVDS() {}

  virtual void initial()
  {
    // enable lighting

    // glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

    // enable tracking material ambient and diffuse from surface color

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // set-up the lighting colors (ambient, diffuse, specular)

    GLfloat light_ambient[]  = { .3f, .3f, .3f, 1.0f }; // ambient light
    GLfloat light_diffuse[]  = { .7f, .7f, .7f, 1.0f }; // diffuse light
    GLfloat light_specular[] = { 1, 1, 1, 1 };          // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // set-up the position of the light

    float light_position[4] = { 0, 0, 1, 0 }; // directional light
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0); // MUST enable each light source after configuration

    // initialize the 2d texture

    m_tex2d.initialize_from_image_file("data\\512x512.bmp");
  }

  virtual void on_display()
  {
    glMatrixMode(GL_PROJECTION_MATRIX);
    gluPerspective(45, 1.F, 0.1, 100);

    glMatrixMode(GL_MODELVIEW_MATRIX);
    glTranslatef(0, 0, -2.5);

    // rotate cube by Y-axis

    static float rotate_angle = 0;
    if (rotate_angle > 360.) rotate_angle = 0;
    rotate_angle += 0.5F;
    glRotatef(rotate_angle, 0, 1, 0);

    // use the 2d for uv mapping on cube

    m_tex2d.use();

    // initialize and define vds format

    // static GLfloat data[] =
    // {
    //   -1, -1, -1,  0, 0, 0,   -1, -1, +1,  0, 0, 1,   -1, +1, +1,  0, 1, 1,   -1, +1, -1,  0, 1, 0,
    //   +1, -1, -1,  1, 0, 0,   +1, -1, +1,  1, 0, 1,   +1, +1, +1,  1, 1, 1,   +1, +1, -1,  1, 1, 0,
    //   -1, -1, -1,  0, 0, 0,   -1, -1, +1,  0, 0, 1,   +1, -1, +1,  1, 0, 1,   +1, -1, -1,  1, 0, 0,
    //   -1, +1, -1,  0, 1, 0,   -1, +1, +1,  0, 1, 1,   +1, +1, +1,  1, 1, 1,   +1, +1, -1,  1, 1, 0,
    //   -1, -1, -1,  0, 0, 0,   -1, +1, -1,  0, 1, 0,   +1, +1, -1,  1, 1, 0,   +1, -1, -1,  1, 0, 0,
    //   -1, -1,  1,  0, 0, 1,   -1, +1, +1,  0, 1, 1,   +1, +1, +1,  1, 1, 1,   +1, -1, +1,  1, 0, 1,
    // };
    // 
    // GLuint offset = 0;
    // GLuint vds_size = 6 * sizeof(GLfloat); // this vds has 2 attributes (position 3f + color 3f = 6f)
    // static VBO vbo(&data, sizeof(data), vds_size);
    // offset = vbo.declare_position_format(offset, 3, GL_FLOAT, vds_size);
    // offset = vbo.declare_color_format(offset, 3, GL_FLOAT, vds_size);
    // vbo.draw(GL_QUADS);

    GLfloat data[] =
    {
      // position array

      +.5f, +.5f, +.5f,  -.5f, +.5f, +.5f,  -.5f, -.5f, +.5f,  +.5f, -.5f, +.5f, // v0,v1,v2,v3 (front)
      +.5f, +.5f, +.5f,  +.5f, -.5f, +.5f,  +.5f, -.5f, -.5f,  +.5f, +.5f, -.5f, // v0,v3,v4,v5 (right)
      +.5f, +.5f, +.5f,  +.5f, +.5f, -.5f,  -.5f, +.5f, -.5f,  -.5f, +.5f, +.5f, // v0,v5,v6,v1 (top)
      -.5f, +.5f, +.5f,  -.5f, +.5f, -.5f,  -.5f, -.5f, -.5f,  -.5f, -.5f, +.5f, // v1,v6,v7,v2 (left)
      -.5f, -.5f, -.5f,  +.5f, -.5f, -.5f,  +.5f, -.5f, +.5f,  -.5f, -.5f, +.5f, // v7,v4,v3,v2 (bottom)
      +.5f, -.5f, -.5f,  -.5f, -.5f, -.5f,  -.5f, +.5f, -.5f,  +.5f, +.5f, -.5f, // v4,v7,v6,v5 (back)

      // normal array

      +0, +0, +1,  +0, +0, +1,  +0, +0, +1,  +0, +0, +1, // v0,v1,v2,v3 (front)
      +1, +0, +0,  +1, +0, +0,  +1, +0, +0,  +1, +0, +0, // v0,v3,v4,v5 (right)
      +0, +1, +0,  +0, +1, +0,  +0, +1, +0,  +0, +1, +0, // v0,v5,v6,v1 (top)
      -1, +0, +0,  -1, +0, +0,  -1, +0, +0,  -1, +0, +0, // v1,v6,v7,v2 (left)
      +0, -1, +0,  +0, -1, +0,  +0, -1, +0,  +0, -1, +0, // v7,v4,v3,v2 (bottom)
      +0, +0, -1,  +0, +0, -1,  +0, +0, -1,  +0, +0, -1, // v4,v7,v6,v5 (back)

      // color array

      +1, +1, +1,  +1, +1, +0,  +1, +0, +0,  +1, +0, +1, // v0,v1,v2,v3 (front)
      +1, +1, +1,  +1, +0, +1,  +0, +0, +1,  +0, +1, +1, // v0,v3,v4,v5 (right)
      +1, +1, +1,  +0, +1, +1,  +0, +1, +0,  +1, +1, +0, // v0,v5,v6,v1 (top)
      +1, +1, +0,  +0, +1, +0,  +0, +0, +0,  +1, +0, +0, // v1,v6,v7,v2 (left)
      +0, +0, +0,  +0, +0, +1,  +1, +0, +1,  +1, +0, +0, // v7,v4,v3,v2 (bottom)
      +0, +0, +1,  +0, +0, +0,  +0, +1, +0,  +0, +1, +1, // v4,v7,v6,v5 (back)

      // texcoord array

      +1, +0,  +0, +0,  +0, +1,  +1, +1, // v0,v1,v2,v3 (front)
      +0, +0,  +0, +1,  +1, +1,  +1, +0, // v0,v3,v4,v5 (right)
      +1, +1,  +1, +0,  +0, +0,  +0, +1, // v0,v5,v6,v1 (top)
      +1, +0,  +0, +0,  +0, +1,  +1, +1, // v1,v6,v7,v2 (left)
      +0, +1,  +1, +1,  +1, +0,  +0, +0, // v7,v4,v3,v2 (bottom)
      +0, +1,  +1, +1,  +1, +0,  +0, +0, // v4,v7,v6,v5 (back)
    };

    GLuint vds_size = (3 + 3 + 3 + 2) * sizeof(GLfloat);
    static VBO vbo(&data, sizeof(data), vds_size);

    GLuint attr_offset, attr_size;

    attr_offset = 0;
    attr_size = vbo.declare_position_format(attr_offset, 3, GL_FLOAT, 0);

    attr_offset += attr_size * vbo.get_num_elements();
    attr_size = vbo.declare_normal_format(attr_offset, 3, GL_FLOAT, 0);

    attr_offset += attr_size * vbo.get_num_elements();
    vbo.declare_color_format(attr_offset, 3, GL_FLOAT, 0);

    attr_offset += attr_size * vbo.get_num_elements();
    attr_size = vbo.declare_texture_format(attr_offset, 2, GL_FLOAT, 0);

    vbo.draw(GL_QUADS);
  }

private:
  glwnd::Tex2D m_tex2d;
};