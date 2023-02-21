#pragma once

/**
 * @file   mesh.h
 * @author Vic P.
 * @brief  Mesh
 */

#include <string>
#include <vector>

#include <gl/glew.h>
#include <glm/glm.hpp>

#include "TinyObjLoader.h"

namespace glwnd
{

class VAO;

class Mesh
{
public:
  using uint16 = std::uint16_t;
  using uint32 = std::uint32_t;

  Mesh(const std::string& name);
  Mesh(Mesh&&) = delete;
  Mesh(const Mesh&) = delete;
  Mesh& operator=(Mesh&&) = delete;
  Mesh& operator=(const Mesh&) = delete;
  virtual ~Mesh();

  int  material_id() const;
  void material_id(int id);

  bool ready() const;
  void load(const tinyobj::shape_t& shape);
  void render();

private:
  std::vector<glm::vec3> m_positions;
  std::vector<glm::vec2> m_texcoords;
  std::vector<glm::vec3> m_normals;
  std::vector<uint16>    m_indices;
  int m_material_id;
  std::string m_name;
  VAO* m_ptr_vao;
  bool m_ready;
};

}; // glwnd