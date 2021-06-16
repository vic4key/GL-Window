#pragma once

/**
 * @file   mesh.h
 * @author Vic P.
 * @brief  Mesh
 */

#include <string>
#include <vector>
#include <cassert>

#include <gl/glew.h>
#include <glm/glm.hpp>

namespace glwnd
{

class Mesh
{
public:
  using uint16 = std::uint16_t;
  using uint32 = std::uint32_t;

  Mesh() = delete;
  Mesh(Mesh&&) = default;
  Mesh(const Mesh&) = delete;
  Mesh& operator=(Mesh&&) = default;
  Mesh& operator=(const Mesh&) = delete;
  Mesh(const std::string& file_path);
  virtual ~Mesh();

  void render();

private:
  std::vector<glm::vec3> m_positions;
  std::vector<glm::vec2> m_texcoords;
  std::vector<glm::vec3> m_normals;
  std::vector<uint16>    m_indices;

  GLuint m_vao;

  GLuint m_vbo_positions;
  GLuint m_vbo_texcoords;
  GLuint m_vbo_normals;
  GLuint m_vbo_elements;
};

}; // glwnd