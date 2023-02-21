/**
 * @file   mesh.cpp
 * @author Vic P.
 * @brief  Mesh
 */

#include "glwnd/mesh.h"
#include "glwnd/utils.h"
#include "glwnd/defs.h"
#include "glwnd/vao.h"

namespace glwnd
{

Mesh::Mesh(const std::string& name) : m_ready(false), m_ptr_vao(new VAO), m_name(name), m_material_id(-1)
{
}

Mesh::~Mesh()
{
  m_ready = false;

  if (m_ptr_vao != nullptr)
  {
    delete m_ptr_vao;
  }
}

int Mesh::material_id() const
{
  return m_material_id;
}

void Mesh::material_id(int id)
{
  m_material_id = id;
}

bool Mesh::ready() const
{
  return m_ready && m_ptr_vao->ready();
}

void Mesh::load(const tinyobj::shape_t& shape)
{
  // positions

  m_positions.reserve(utils::align_up(shape.mesh.positions.size() / 3));

  for (uint32 i = 0; i < shape.mesh.positions.size(); i += 3)
  {
    m_positions.emplace_back(glm::vec3(
      shape.mesh.positions[i],
      shape.mesh.positions[i + 1],
      shape.mesh.positions[i + 2]));
  }

  // texcoords

  m_texcoords.reserve(utils::align_up(shape.mesh.texcoords.size() / 2));

  for (uint32 i = 0; i < shape.mesh.texcoords.size(); i += 2)
  {
    m_texcoords.emplace_back(glm::vec2(
      shape.mesh.texcoords[i],
      shape.mesh.texcoords[i + 1]));
  }

  // normals

  m_normals.reserve(utils::align_up(shape.mesh.normals.size() / 3));

  for (uint32 i = 0; i < shape.mesh.normals.size(); i += 3)
  {
    m_normals.emplace_back(glm::vec3(
      shape.mesh.normals[i],
      shape.mesh.normals[i + 1],
      shape.mesh.normals[i + 2]));
  }

  // m_indices

  m_indices.reserve(shape.mesh.indices.size());

  for (uint32 i = 0; i < shape.mesh.indices.size(); i++)
  {
    m_indices.emplace_back(shape.mesh.indices[i]);
  }

  // Fatal error - one of the vectors is empty and it will cause problems with OpenGL buffers.
  // Program must be closed.

  std::string warning = "";

  if (m_positions.empty())
  {
    warning.append("vertices");
  }

  if (m_texcoords.empty())
  {
    if (warning.length() != 0)
    {
      warning.append(", ");
    }

    warning.append("texcoords");
  }

  if (m_normals.empty())
  {
    if (warning.length() != 0)
    {
      warning.append(", ");
    }

    warning.append("normals");
  }

  if (m_indices.empty())
  {
    if (warning.length() != 0)
    {
      warning.append(", ");
    }

    warning.append("indices");
  }

  if (warning.length() != 0)
  {
    utils::log("model is missing: %s", warning.c_str());
  }

  m_ptr_vao->setup_begin();
  {
    // Note: The order depends on the shader files
    m_ptr_vao->declare_position_format({ m_positions.data(), size_of(m_positions) }, 3, GL_FLOAT);
    m_ptr_vao->declare_normal_format({ m_normals.data(), size_of(m_normals) }, 3, GL_FLOAT);
    m_ptr_vao->declare_texcoord_format({ m_texcoords.data(), size_of(m_texcoords) }, 2, GL_FLOAT);
    m_ptr_vao->declare_index_format({ m_indices.data(), size_of(m_indices) }, 1, GL_UNSIGNED_SHORT);
  }
  m_ptr_vao->setup_end();

  m_ready = true;
}

void Mesh::render()
{
  if (!m_ready)
  {
    throw std::runtime_error("mesh is not ready to render");
  }

  m_ptr_vao->render(GL_TRIANGLES);
}

}; // glwnd