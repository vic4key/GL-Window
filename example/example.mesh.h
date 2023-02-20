#pragma once

#include "example.h"

#include <glwnd/mesh.h>
#include <glwnd/shader.h>

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

static Mesh m_mesh; // for sharing between views

class GLViewExampleMesh : public GLView
{
public:
  GLViewExampleMesh() : GLView() {}
  virtual ~GLViewExampleMesh() {}

  virtual void initial()
  {
    // setup ImGui dialog
    dear_imgui_cfg cfg;
    cfg.style = dear_imgui_cfg::styles::IMGUI_CLASSIC;
    cfg.font_path = "C:\\Windows\\Fonts\\georgia.ttf";
    cfg.font_size = 16.F;
    this->parent().enable_dear_imgui(true, &cfg);

    // demo model 1
    static model_t monkey;
    monkey.n = "assets\\monkey.obj";
    monkey.t = glm::vec3(0.F);
    monkey.r = glm::vec3(0.F, 180.F, 0.F);
    monkey.s = glm::vec3(1.F);
    monkey.c = glm::vec3(0.F, 1.F, 0.F);
    monkey.p = glm::vec3(0.F, 0.F, 0.F);
    monkey.d = glm::vec3(0.F, 1.F, 0.F);
    monkey.a = false;

    // demo model 2
    static model_t scene;
    scene.n = "assets\\scene.obj";
    scene.t = glm::vec3(0.5F, -0.5F, 0.F);
    scene.r = glm::vec3(-10.F, 120.F, 0.F);
    scene.s = glm::vec3(0.5F);
    scene.c = glm::vec3(1.F, 1.F, 1.F);
    scene.p = glm::vec3(0.F, 0.F, 0.F);
    scene.d = glm::vec3(0.F, 1.F, 0.F);
    scene.a = true;

    // select a demo model for loading & rendering
    m_model = scene;

    if (!m_mesh.ready())
    {
      m_mesh.load(m_model.n);
    }

    m_shader.build_file("assets\\lighting.vert", "assets\\lighting.frag");
  }

  virtual void on_display()
  {
    // display ImGui dialog - color sider
    ImGui::Begin("ImGui Color Slider");
    {
      static float v[3] = { m_model.c.r, m_model.c.g, m_model.c.b };
      ImGui::ColorEdit3("RGB", v);
      m_model.c = glm::make_vec3(v);
    }
    ImGui::End();

    // demo combine the built-in model-view matrix of the current context with user-defined matrix
    {
      GLfloat eyes[4][3] =
      {
        {+0.F, 0.F, +.5F}, // from front
        {+0.F, 0.F, -.5F}, // from back
        {+.5F, 0.F, +0.F}, // turn left
        {-.5F, 0.F, +0.F}, // turn right
      };

      const auto& eye = eyes[this->index()];
      const auto& pos = m_model.p;
      const auto& dir = m_model.d;

      gluLookAt(eye[0], eye[1], eye[2], pos.x, pos.y, pos.z, dir.x, dir.y, dir.z);
    }

    // view matrix
    glm::vec3 eye(0.F, 0.F, -15.F);
    glm::vec3 pos = m_model.p;
    glm::vec3 dir = m_model.d;
    glm::mat4 mtx_view = glm::lookAt(eye, pos, dir);
    mtx_view *= this->get_context_matrix(GL_MODELVIEW_MATRIX);

    // projection matrix
    auto win = this->viewport().coordinate().win;
    glm::mat4 mtx_projection = glm::perspective(15.F, win.aspect(), 0.1F, 20.F);

    // model matrix
    if (m_model.a && m_model.r.y++ > 360.F) m_model.r.y = 0.F;
    glm::mat4 mtx_model = this->transform_matrix(m_model.t, m_model.r, m_model.s);

    // enable shader
    m_shader.use(true);

    // setup mesh
    m_shader.set_variable("color", m_model.c);
    m_shader.set_variable("target", m_model.p);

    // setup camera and mvp matrix
    m_shader.set_variable("model", mtx_model);
    m_shader.set_variable("view", mtx_view);
    m_shader.set_variable("projection", mtx_projection);

    // setup lighting
    glm::vec3 light_position(-3.F, 6.F, -3.F);
    m_shader.set_variable("light.direction", light_position);
    m_shader.set_variable("light.ambient",  glm::vec3(0.2f, 0.23f, 0.25f));
    m_shader.set_variable("light.diffuse",  glm::vec3(0.6f, 0.63f, 0.65f));
    m_shader.set_variable("light.specular", glm::vec3(0.0f));

    // render mesh
    m_mesh.render();

    // disable shader
    m_shader.use(false);
  }

private:
  // Mesh m_mesh;
  Shader m_shader;

  struct model_t
  {
    std::string n; // name
    glm::vec3 t, r, s, c, p, d; // translate, rotate, scale, color, position, direction (pitch, yaw, roll)
    bool a = false; // animate
  };
  
  model_t m_model;
};