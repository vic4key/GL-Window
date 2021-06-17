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

  void use() const;

  GLint location(const std::string& name) const;
  void  uniform(const std::string& name, bool value) const;
  void  uniform(const std::string& name, int32 value) const;
  void  uniform(const std::string& name, float value) const;
  void  uniform(const std::string& name, glm::vec2 value) const;
  void  uniform(const std::string& name, glm::vec3 value) const;
  void  uniform(const std::string& name, glm::mat4 value) const;

private:
  GLuint compile(const GLchar* source, GLuint shaderType);

private:
  GLuint m_id;
};

}; // glwnd