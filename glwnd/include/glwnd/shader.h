#pragma once

/**
 * @file   shader.h
 * @author Vic P.
 * @brief  Shader
 */

#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>

namespace glwnd
{

class Shader
{
public:
  using int32 = std::int32_t;

  Shader();
  virtual ~Shader();

  void build_file(const std::string& vertex_file_path, const std::string& fragment_file_path);
  void build_code(const char* vertex_source_code, const char* fragment_source_code);

  void use(bool state = true) const;

  void set_variable(const std::string& name, const int   value) const;
  void set_variable(const std::string& name, const bool  value) const;
  void set_variable(const std::string& name, const float value) const;
  void set_variable(const std::string& name, const glm::vec2& value) const;
  void set_variable(const std::string& name, const glm::vec3& value) const;
  void set_variable(const std::string& name, const glm::mat4& value) const;

private:
  GLuint compile(const GLchar* source, GLuint shaderType);
  GLint get_variable_location(const std::string& name) const;

private:
  GLuint m_id;
};

}; // glwnd