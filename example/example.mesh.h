#pragma once

#include "example.h"

#include <glwnd/shader.h>
#include <glwnd/mesh.h>

#include <glm/gtc/matrix_transform.hpp>

class GLWindowExampleMesh : public GLWindow
{
public:
  GLWindowExampleMesh() : GLWindow() {}
  virtual ~GLWindowExampleMesh() {}

  virtual void initial()
  {
    m = std::make_unique<Mesh>("assets\\monkey.obj");
    shader = std::make_unique<Shader>("shaders\\shadow_mapping.vert", "shaders\\shadow_mapping.frag");
  }

  virtual void on_display()
  {
    // Light calculations.
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    glm::vec3 lightPosition(glm::vec3(-3.0f, 6.0f, -3.0f));
    GLfloat near_plane = 1.0f, far_plane = 30.0f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(1.0));
    lightSpaceMatrix = lightProjection * lightView;

    auto position = glm::vec3(1.0f, 1.0f, 1.0f);

    float distance = 15.0f;
    float verticalAngle   = -60.f;
    float horizontalAngle = +0.f;

    float FOV = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 20.0f;
    float moveSpeed = 0.1f;
    float aspectRatio = 16.0f / 9.0f;

    const float PI = 3.14156f;

    auto getView = [&]() -> glm::mat4
    {
      auto target = glm::vec3(
        distance * -sinf(horizontalAngle * (PI / 180.0f)) * cosf((verticalAngle) * (PI / 180.0f)),
        distance * -sinf(verticalAngle * (PI / 180.0f)),
        -distance * cosf(horizontalAngle * (PI / 180.0f)) * cosf((verticalAngle) * (PI / 180.0f))
      );

      return glm::lookAt(target + position,
        position,
        glm::vec3(0.0f, 1.0f, 0.0f)
      );
    };

    auto getProjection = [&]() -> glm::mat4
    {
      return glm::perspective(FOV, aspectRatio, nearPlane, farPlane);
    };

    auto getModelMatrix = [&](glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) -> glm::mat4
    {
      glm::mat4 unit(1);
      return unit
        * glm::translate(unit, translate)
        * glm::rotate(unit, rotate.x, glm::vec3(1.0f, 0.0f, 0.0f)) // x
        * glm::rotate(unit, rotate.y, glm::vec3(0.0f, 1.0f, 0.0f)) // y
        * glm::rotate(unit, rotate.z, glm::vec3(0.0f, 0.0f, 1.0f)) // z
        * glm::scale(unit, scale);
    };

    shader->use();

    shader->setUniform("projection", getProjection());
    shader->setUniform("view", getView());

    shader->setUniform("viewPosition", position);
    shader->setUniform("lightSpaceMatrix", lightSpaceMatrix);

    shader->setUniform("light.direction", lightPosition);
    shader->setUniform("light.ambient", glm::vec3(0.2f, 0.23f, 0.25f));
    shader->setUniform("light.diffuse", glm::vec3(0.6f, 0.63f, 0.65f));
    shader->setUniform("light.specular", glm::vec3(0.0f));

    shader->setUniform(
      "model",
      getModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f)));

    m->render();
  }

private:
  std::unique_ptr<Mesh> m;
  std::shared_ptr<Shader> shader;
};