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

  Shader(const std::string& vertex_file_path, const std::string& fragment_file_path);
  Shader() = delete;
  Shader(const Shader&) = default;
  Shader(Shader&&) = default;
  Shader& operator=(const Shader&) = default;
  Shader& operator=(Shader&&) = default;
  virtual ~Shader();

  void use() const;

  GLint location(const std::string& name) const;
  void  uniform(const std::string& name, bool value) const;
  void  uniform(const std::string& name, int32 value) const;
  void  uniform(const std::string& name, float value) const;
  void  uniform(const std::string& name, glm::vec2 value) const;
  void  uniform(const std::string& name, glm::vec3 value) const;
  void  uniform(const std::string& name, glm::mat4 value) const;

private:
  std::string load_text_file(const std::string& file_path);
  GLuint compile(const GLchar* source, GLuint shaderType);

private:
  GLuint m_id = -1;
};

}; // glwnd