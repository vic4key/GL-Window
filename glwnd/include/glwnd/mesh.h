#pragma once

/**
 * @file   mesh.h
 * @author Vic P.
 * @brief  Mesh
 */

#include <string>
#include <vector>

#include "defs.h"
#include "vao.h"

#include "TinyObjLoader.h"

namespace glwnd
{

class VAO;

class Mesh
{
public:
  Mesh(const std::string& name);
  Mesh(Mesh&&) = delete;
  Mesh(const Mesh&) = delete;
  Mesh& operator=(Mesh&&) = delete;
  Mesh& operator=(const Mesh&) = delete;
  virtual ~Mesh();

  GLuint material_id() const;
  void material_id(GLuint id);

  bool ready() const;
  void load(const tinyobj::shape_t& shape);
  void load(const std::vector<vertex_t>& vertices, const std::vector<uint16>& indices, const GLuint material_id);
  void render();

private:
  bool m_ready;
  VAO  m_vao;
  std::string m_name;
  GLuint m_material_id;

  std::vector<glm::vec3> m_positions;
  std::vector<glm::vec2> m_texcoords;
  std::vector<glm::vec3> m_normals;
  std::vector<uint16>    m_indices;
};

}; // glwnd