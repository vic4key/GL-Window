#pragma once

#include "example.h"

#include <glwnd/mesh.h>
#include <glwnd/shader.h>
#include <glwnd/viewport.h>
#include <glwnd/geometry.h>
#include <glwnd/view.h>
#include <glwnd/layout.h>

class GLWindowExampleMesh : public GLWindow
{
public:
  GLWindowExampleMesh() : GLWindow() {}
  virtual ~GLWindowExampleMesh() {}

  virtual void initial()
  {
    this->set_layout(GLLayout::_2x2(*this));

    m_mesh.load("assets\\monkey.obj");
    m_shader.build_file("assets\\lighting.vert", "assets\\lighting.frag");
  }

  virtual void on_display(GLView& view)
  {
    glm::vec3 target_color(0.F, 1.F, 0.F);
    glm::vec3 target_position(0.F, 0.F, 0.F);
    glm::vec3 target_direction(0.F, 1.F, 0.F); // (pitch, yaw, roll)
    glm::vec3 light_position(-3.F, 6.F, -3.F);

    // demo that combine the buit-in model-view matrix of the current context with user-defined matrix
    {
      GLfloat eyes[4][3] =
      {
        {+0.F, 0.F, +.5F}, // from front
        {+0.F, 0.F, -.5F}, // from back
        {+.5F, 0.F, +0.F}, // turn left
        {-.5F, 0.F, +0.F}, // turn right
      };

      const auto& eye = eyes[view.index()];
      const auto& pos = target_position;
      const auto& dir = target_direction;

      gluLookAt(eye[0], eye[1], eye[2], pos.x, pos.y, pos.z, dir.x, dir.y, dir.z);
    }

    // view matrix
    glm::vec3 eye(0.F, 0.F, -15.F);
    glm::vec3 pos = target_position;
    glm::vec3 dir = target_direction;
    glm::mat4 mtx_view = glm::lookAt(eye, pos, dir);
    mtx_view *= view.get_context_matrix(GL_MODELVIEW_MATRIX);

    // projection matrix
    auto  win = this->viewport().coordinate().win;
    float ratio = float(win.width()) / float(win.height());
    glm::mat4 mtx_projection = glm::perspective(15.F, ratio, 0.1F, 20.F);

    // model matrix
    static float angle = 180.F;
    // if (angle++ > 360.F) angle = 0.F;
    glm::mat4 mtx_model(1.F);
    mtx_model *= glm::rotate(mtx_model, angle, glm::vec3(0.F, 1.F, 0.F));

    // setup mesh
    m_shader.uniform("color", target_color);
    m_shader.uniform("target", target_position);

    // setup camera and mvp matrix
    m_shader.uniform("model", mtx_model);
    m_shader.uniform("view", mtx_view);
    m_shader.uniform("projection", mtx_projection);

    // setup lighting
    m_shader.uniform("light.direction", light_position);
    m_shader.uniform("light.ambient", glm::vec3(0.2f, 0.23f, 0.25f));
    m_shader.uniform("light.diffuse", glm::vec3(0.6f, 0.63f, 0.65f));
    m_shader.uniform("light.specular", glm::vec3(0.0f));

    // using lighting shader
    m_shader.use();

    // render mesh
    m_mesh.render();
  }

private:
  Mesh m_mesh;
  Shader m_shader;
};