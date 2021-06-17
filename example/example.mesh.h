#pragma once

#include "example.h"

#include <glwnd/mesh.h>

class GLWindowExampleMesh : public GLWindow
{
public:
  GLWindowExampleMesh() : GLWindow() {}
  virtual ~GLWindowExampleMesh() {}

  virtual void initial()
  {
    m_mesh.load("assets\\monkey.obj");
    m_tex.initialize_from_image_file("assets\\128x128.bmp");

    // enable lighting

    glEnable(GL_LIGHTING);

    // enable tracking material ambient and diffuse from surface color

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // set-up the lighting colors (ambient, diffuse, specular)

    GLfloat light_ambient[]  = { 0.2F, 0.23F, 0.25F };
    GLfloat light_diffuse[]  = { 0.6F, 0.63F, 0.65F };
    GLfloat light_specular[] = { 1.F, 1.F, 1.F, 1.F };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // set-up the position of the light

    float light_position[4] = { 0.F, 0.F, -1.F, 0.F };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0); // MUST enable each light source after configuration

    // set-up others

    // glDisable(GL_BLEND);

    // glEnable(GL_TEXTURE_2D);
    // glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION_MATRIX);
    gluPerspective(45, 1., 0.1, 10.);

    glMatrixMode(GL_MODELVIEW_MATRIX);
    glTranslatef(0., 0., -4.);
  }

  virtual void on_display()
  {
    // rotate cube by Y-axis

    static float rotate_angle = 0;
    if (rotate_angle++ > 360.) rotate_angle = 0;
    glRotatef(rotate_angle, 0, 1, 0);

    // map texture and render mesh

    // m_tex.use();
    m_mesh.render();
  }

private:
  Mesh m_mesh;
  Tex2D m_tex;
};