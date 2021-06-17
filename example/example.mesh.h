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
  }

  virtual void on_display()
  {
    glMatrixMode(GL_PROJECTION_MATRIX);
    gluPerspective(45, 1., 0.1, 10.);

    glMatrixMode(GL_MODELVIEW_MATRIX);
    glTranslatef(0., 0., -4.);

    glDisable(GL_BLEND);

    // rotate cube by Y-axis

    static float rotate_angle = 0;
    if (rotate_angle++ > 360.) rotate_angle = 0;
    glRotatef(rotate_angle, 0, 1, 0);

    // render mesh of 3d object

    m_mesh.render();
  }

private:
  Mesh m_mesh;
};