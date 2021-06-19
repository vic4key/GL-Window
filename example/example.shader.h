#pragma once

#include "example.h"

#include <glwnd/shader.h>

class GLWindowExampleShader : public GLWindow
{
public:
  GLWindowExampleShader() : GLWindow(), m_vbo(0), m_vao(0) {}
  virtual ~GLWindowExampleShader() {}

  virtual void initial()
  {
    const char* vertex_shader_source = R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 color;
      out vec3 vertexColor;
      void main()
      {
        gl_Position = vec4(position, 1.0);
        vertexColor = color;
      })";

    const char* fragment_shader_source = R"(
      #version 330 core
      in  vec3 vertexColor;
      out vec4 fragColor;
      void main()
      {
        fragColor = vec4(vertexColor, 1.0f);
      };)";

    m_shader.build_code(vertex_shader_source, fragment_shader_source);

    float data[] =
    {
      -0.5F, -0.5F, +0.F, +1.F, +0.F, +0.F, // r
      +0.5F, -0.5F, +0.F, +0.F, +1.F, +0.F, // g
      +0.0F, +0.5F, +0.F, +0.F, +0.F, +1.F  // b
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }

  virtual void final()
  {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_vbo);
  }

  virtual void on_display(GLView& view)
  {
    m_shader.use();

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  GLuint m_vbo;
  GLuint m_vao;
  Shader m_shader;
};