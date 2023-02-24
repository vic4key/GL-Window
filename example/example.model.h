#pragma once

#include "example.h"

#include <glwnd/model.h>
#include <glwnd/shader.h>

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

static Model m_model_material; // static for sharing between views

class GLViewExampleModel : public GLView
{
public:
  GLViewExampleModel() : GLView() {}
  virtual ~GLViewExampleModel() {}

  virtual void initial()
  {
    // model chest
    static model_t chest;
    chest.n = "assets\\Chest\\Chest.obj";
    chest.t = glm::vec3(0.F, 0.F, 0.F);
    chest.r = glm::vec3(-10.F, 120.F, 0.F);
    chest.s = glm::vec3(2.F);
    chest.c = glm::vec3(1.F, 1.F, 1.F);
    chest.p = glm::vec3(0.F, 0.F, 0.F);
    chest.d = glm::vec3(0.F, 1.F, 0.F);
    chest.a = true;

    // model raptor
    static model_t raptor;
    raptor.n = "assets\\Raptor\\Raptor.obj";
    raptor.t = glm::vec3(0.0F);
    raptor.r = glm::vec3(0.0F, 0.F, 0.0F);
    raptor.s = glm::vec3(0.5F);
    raptor.c = glm::vec3(0.0F, 1.F, 0.0F);
    raptor.p = glm::vec3(0.0F, 0.F, 0.0F);
    raptor.d = glm::vec3(0.0F, 1.F, 0.0F);
    raptor.a = true;

    // model bench
    static model_t bench;
    bench.n = "assets\\Bench\\bench.obj";
    bench.t = glm::vec3(0.0F, -0.5F, 0.F);
    bench.r = glm::vec3(0.0F, 0.F, 0.0F);
    bench.s = glm::vec3(0.2F);
    bench.c = glm::vec3(0.0F, 1.F, 0.0F);
    bench.p = glm::vec3(0.0F, 0.F, 0.0F);
    bench.d = glm::vec3(0.0F, 1.F, 0.0F);
    bench.a = true;

    // model teapot
    static model_t teapot;
    teapot.n = "assets\\Teapot\\teapot.obj";
    teapot.t = glm::vec3(0.0F, -0.5F, 0.F);
    teapot.r = glm::vec3(0.0F, 0.F, 0.0F);
    teapot.s = glm::vec3(0.02F);
    teapot.c = glm::vec3(0.0F, 1.F, 0.0F);
    teapot.p = glm::vec3(0.0F, 0.F, 0.0F);
    teapot.d = glm::vec3(0.0F, 1.F, 0.0F);
    teapot.a = true;

    // model wolf
    static model_t wolf;
    wolf.n = "assets\\Wolf\\Wolf.obj";
    wolf.t = glm::vec3(0.0F, -1.0F, 0.F);
    wolf.r = glm::vec3(0.0F, 0.F, 0.0F);
    wolf.s = glm::vec3(0.7F);
    wolf.c = glm::vec3(0.0F, 1.F, 0.0F);
    wolf.p = glm::vec3(0.0F, 0.F, 0.0F);
    wolf.d = glm::vec3(0.0F, 1.F, 0.0F);
    wolf.a = true;

    // model house
    static model_t house;
    house.n = "assets\\House\\house.3ds";
    house.t = glm::vec3(0.0F, -1.0F, 0.F);
    house.r = glm::vec3(0.0F, 0.F, 0.0F);
    house.s = glm::vec3(0.5F);
    house.c = glm::vec3(0.0F, 1.F, 0.0F);
    house.p = glm::vec3(0.0F, 0.F, 0.0F);
    house.d = glm::vec3(0.0F, 1.F, 0.0F);
    house.a = true;

    // model suzanne
    static model_t suzanne;
    suzanne.n = "assets\\Suzanne\\Suzanne.obj";
    suzanne.t = glm::vec3(0.0F, 0.0F, 0.F);
    suzanne.r = glm::vec3(0.0F, 180.F, 0.0F);
    suzanne.s = glm::vec3(1.0F);
    suzanne.c = glm::vec3(0.0F, 1.F, 0.0F);
    suzanne.p = glm::vec3(0.0F, 0.F, 0.0F);
    suzanne.d = glm::vec3(0.0F, 1.F, 0.0F);
    suzanne.a = true;

    // model cyborg
    static model_t cyborg;
    cyborg.n = "assets\\Cyborg\\cyborg.obj";
    cyborg.t = glm::vec3(0.0F, -1.0F, 0.F);
    cyborg.r = glm::vec3(0.0F, 180.F, 0.0F);
    cyborg.s = glm::vec3(0.7F);
    cyborg.c = glm::vec3(0.0F, 1.F, 0.0F);
    cyborg.p = glm::vec3(0.0F, 0.F, 0.0F);
    cyborg.d = glm::vec3(0.0F, 1.F, 0.0F);
    cyborg.a = true;

    // model gun
    static model_t gun;
    gun.n = "assets\\GUNs\\guns2.obj";
    gun.t = glm::vec3(0.0F, -1.0F, 0.F);
    gun.r = glm::vec3(0.0F, 180.F, 0.0F);
    gun.s = glm::vec3(0.3F);
    gun.c = glm::vec3(0.0F, 1.F, 0.0F);
    gun.p = glm::vec3(0.0F, 0.F, 0.0F);
    gun.d = glm::vec3(0.0F, 1.F, 0.0F);
    gun.a = true;

    // select a demo model for loading & rendering
    m_model = gun;

    if (!m_model_material.ready())
    {
      m_model_material.load(m_model.n);
    }

    m_shader.build_file("assets\\shader\\model.vs", "assets\\shader\\model.fs");
  }

  virtual void on_display()
  {
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
    if (m_model.a)
    {
      m_model.r.y += 0.3F;
      if (m_model.r.y > 360.F) m_model.r.y = 0.F;
    }
    glm::mat4 mtx_model = this->transform_matrix(m_model.t, m_model.r, m_model.s);

    // enable shader
    m_shader.use(true);

    // setup camera and mvp matrix
    m_shader.set_variable("model", mtx_model);
    m_shader.set_variable("view",  mtx_view);
    m_shader.set_variable("projection", mtx_projection);

    // setup model
    m_shader.set_variable("target", m_model.p);
    // m_shader.set_variable("color",  m_model.c);

    // render model
    m_model_material.render(m_shader);

    // disable shader
    m_shader.use(false);
  }

private:
  Shader m_shader;

  struct model_t
  {
    std::string n; // name
    glm::vec3 t, r, s, c, p, d; // translate, rotate, scale, color, position, direction (pitch, yaw, roll)
    bool a = false; // animate
  };

  model_t m_model;
};