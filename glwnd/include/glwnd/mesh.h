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

class VAO;
class Tex2D;
struct Material;

class Mesh
{
public:
  using uint16 = std::uint16_t;
  using uint32 = std::uint32_t;

  Mesh();
  Mesh(Mesh&&) = default;
  Mesh(const Mesh&) = delete;
  Mesh& operator=(Mesh&&) = default;
  Mesh& operator=(const Mesh&) = delete;
  virtual ~Mesh();

  bool ready() const;
  void load(const std::string& obj_file_path);
  void render();

private:
  std::vector<glm::vec3> m_positions;
  std::vector<glm::vec2> m_texcoords;
  std::vector<glm::vec3> m_normals;
  std::vector<uint16>    m_indices;
  std::vector<Material*> m_materials;
  VAO* m_ptr_vao;
  bool m_ready;
};

}; // glwnd