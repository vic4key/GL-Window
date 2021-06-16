/**
 * @file   shader.cpp
 * @author Vic P.
 * @brief  Shader
 */

#include "glwnd/shader.h"

#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

namespace glwnd
{

Shader::Shader(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
  assert(!vertex_file_path.empty());
  assert(!fragment_file_path.empty());

  std::string vertex_source_code = this->load_text_file(vertex_file_path);
  assert(!vertex_source_code.empty());

  std::string fragment_source_code = this->load_text_file(fragment_file_path);
  assert(!fragment_source_code.empty());

  GLuint vertex_compiled = compile(vertex_source_code.c_str(), GL_VERTEX_SHADER);
  GLuint fragment_compiled = compile(fragment_source_code.c_str(), GL_FRAGMENT_SHADER);

  m_id = glCreateProgram();
  glAttachShader(m_id, vertex_compiled);
  glAttachShader(m_id, fragment_compiled);
  glLinkProgram(m_id);

  GLint success = 0;
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  assert(success);

  glDeleteShader(vertex_compiled);
  glDeleteShader(fragment_compiled);
}

Shader::~Shader()
{
  if (m_id != -1)
  {
    glDeleteProgram(m_id);
  }
}

std::string Shader::load_text_file(const std::string& file_path)
{
  std::ifstream t(file_path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
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