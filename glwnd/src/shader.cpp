/**
 * @file   shader.cpp
 * @author Vic P.
 * @brief  Shader
 */

#include "glwnd/shader.h"
#include "glwnd/utils.h"

#include <glm/gtc/type_ptr.hpp>

namespace glwnd
{

Shader::Shader() : m_id(-1)
{
  m_id = glCreateProgram();
}

Shader::~Shader()
{
  if (m_id != -1)
  {
    glDeleteProgram(m_id);
  }
}

void Shader::build_file(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
  assert(!vertex_file_path.empty());
  assert(!fragment_file_path.empty());

  auto vertex_source_code = utils::load_text_file(vertex_file_path);
  assert(!vertex_source_code.empty());

  auto fragment_source_code = utils::load_text_file(fragment_file_path);
  assert(!fragment_source_code.empty());

  this->build_code(vertex_source_code.c_str(), fragment_source_code.c_str());
}

void Shader::build_code(const char* vertex_source_code, const char* fragment_source_code)
{
  assert(m_id != -1);

  GLuint vertex_compiled = this->compile(vertex_source_code, GL_VERTEX_SHADER);
  GLuint fragment_compiled = this->compile(fragment_source_code, GL_FRAGMENT_SHADER);

  glAttachShader(m_id, vertex_compiled);
  glAttachShader(m_id, fragment_compiled);
  glLinkProgram(m_id);

  GLint success = 0;
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  assert(success);

  glDeleteShader(vertex_compiled);
  glDeleteShader(fragment_compiled);
}

GLuint Shader::compile(const GLchar* source, GLuint shaderType)
{
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, 0);
  glCompileShader(shader);

  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  assert(success);

  return shader;
}

void Shader::use() const
{
  assert(m_id != -1);
  glUseProgram(m_id);
}

GLint Shader::location(const std::string& name) const
{
  return glGetUniformLocation(m_id, name.c_str());
}

void Shader::uniform(const std::string& name, bool value) const
{
  glUniform1i(this->location(name), value);
}

void Shader::uniform(const std::string& name, int32 value) const
{
  glUniform1i(this->location(name), value);
}

void Shader::uniform(const std::string& name, float value) const
{
  glUniform1f(this->location(name), value);
}

void Shader::uniform(const std::string& name, glm::vec2 value) const
{
  glUniform2f(this->location(name), value.x, value.y);
}

void Shader::uniform(const std::string& name, glm::vec3 value) const
{
  glUniform3f(this->location(name), value.x, value.y, value.z);
}

void Shader::uniform(const std::string& name, glm::mat4 value) const
{
  glUniformMatrix4fv(this->location(name), 1, GL_FALSE, glm::value_ptr(value));
}

}; // glwnd