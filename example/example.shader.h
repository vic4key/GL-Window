#pragma once

#include "example.h"

class GLWindowExampleShader : public GLWindow
{
public:
  GLWindowExampleShader() : GLWindow(), m_vbo(0), m_vao(0), m_shader_program(-1) {};
  virtual ~GLWindowExampleShader() {};

  virtual void initial()
  {
    const char* vertex_shader_source =
      "#version 330 core\n"
      "layout (location = 0) in vec3 position;\n"
      "layout (location = 1) in vec3 color;\n"
      "out vec3 vertexColor;\n"
      "void main()\n"
      "{\n"
      "    gl_Position = vec4(position, 1.0);\n"
      "    vertexColor = color;\n"
      "}\n";

    const char* fragment_shader_source =
      "#version 330 core\n"
      "out vec4 fragColor;\n"
      "in vec3 vertexColor;\n"
      "void main()\n"
      "{\n"
      "     fragColor = vec4(vertexColor, 1.0f);\n"
      "}\n";

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, vertex_shader);
    glAttachShader(m_shader_program, fragment_shader);
    glLinkProgram(m_shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    float vertices[] =
    {
      -0.5F, -0.5F, 0.F, 1.F, 0.F, 0.F, // r
       0.5F, -0.5F, 0.F, 0.F, 1.F, 0.F, // g
       0.0F,  0.5F, 0.F, 0.F, 0.F, 1.F  // b
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

  virtual void on_display()
  {
    glUseProgram(m_shader_program);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  GLuint m_vbo;
  GLuint m_vao;
  GLuint m_shader_program;
};