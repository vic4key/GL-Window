/**
 * @file   mesh.cpp
 * @author Vic P.
 * @brief  Mesh
 */

#include "glwnd/mesh.h"
#include "glwnd/utils.h"
#include "glwnd/defs.h"
#include "glwnd/vao.h"

#include "TinyObjLoader.h"

namespace glwnd
{

Mesh::Mesh() : m_ptr_vao(new VAO)
{
}

Mesh::~Mesh()
{
  if (m_ptr_vao != nullptr)
  {
    delete m_ptr_vao;
  }
}

bool Mesh::ready() const
{
  return m_ptr_vao->ready();
}

void Mesh::load(const std::string& file_path)
{
  assert(!file_path.empty());

  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  tinyobj::LoadObj(shapes, materials, file_path.c_str());

  // positions

  m_positions.reserve(utils::align_up(shapes[0].mesh.positions.size() / 3));

  for (uint32 i = 0; i < shapes[0].mesh.positions.size(); i += 3)
  {
    m_positions.push_back(glm::vec3(
      shapes[0].mesh.positions[i],
      shapes[0].mesh.positions[i + 1],
      shapes[0].mesh.positions[i + 2]));
  }

  // texcoords

  m_texcoords.reserve(utils::align_up(shapes[0].mesh.texcoords.size() / 2));

  for (uint32 i = 0; i < shapes[0].mesh.texcoords.size(); i += 2)
  {
    m_texcoords.push_back(glm::vec2(
      shapes[0].mesh.texcoords[i],
      shapes[0].mesh.texcoords[i + 1]));
  }

  // normals

  m_normals.reserve(utils::align_up(shapes[0].mesh.normals.size() / 3));

  for (uint32 i = 0; i < shapes[0].mesh.normals.size(); i += 3)
  {
    m_normals.push_back(glm::vec3(
      shapes[0].mesh.normals[i],
      shapes[0].mesh.normals[i + 1],
      shapes[0].mesh.normals[i + 2]));
  }

  // m_indices

  m_indices.reserve(shapes[0].mesh.indices.size());

  for (uint32 i = 0; i < shapes[0].mesh.indices.size(); i++)
  {
    m_indices.push_back(shapes[0].mesh.indices[i]);
  }

  // Fatal error - one of the vectors is empty and it will cause problems with OpenGL buffers.
  // Program must be closed.

  if (m_positions.empty() || m_texcoords.empty() || m_normals.empty())
  {
    std::string info = "";

    if (m_positions.empty())
    {
      info.append("vertices");
    }

    if (m_texcoords.empty())
    {
      if (info.length() != 0)
      {
        info.append(", ");
      }

      info.append("uvs");
    }

    if (m_normals.empty())
    {
      if (info.length() != 0)
      {
        info.append(", ");
      }

      info.append("normals");
    }

    assert(0 && "no data in mesh from file");
  }

  m_ptr_vao->setup_begin();
  {
    m_ptr_vao->declare_position_format({ &m_positions[0], size_of(m_positions) }, 3, GL_FLOAT);
    m_ptr_vao->declare_texcoord_format({ &m_texcoords[0], size_of(m_texcoords) }, 2, GL_FLOAT);
    m_ptr_vao->declare_normal_format({ &m_normals[0], size_of(m_normals) }, 3, GL_FLOAT);
    m_ptr_vao->declare_index_format({ &m_indices[0], size_of(m_indices) }, 1, GL_UNSIGNED_SHORT);
  }
  m_ptr_vao->setup_end();
}

void Mesh::render()
{
  m_ptr_vao->render(GL_TRIANGLES);
}

}; // glwnd