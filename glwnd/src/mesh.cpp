/**
 * @file   mesh.cpp
 * @author Vic P.
 * @brief  Mesh
 */

#include "glwnd/mesh.h"
#include "glwnd/utils.h"

#include "TinyObjLoader.h"

namespace glwnd
{

Mesh::Mesh() : m_vao(-1), m_vbo_positions(-1), m_vbo_texcoords(-1), m_vbo_normals(-1), m_vbo_elements(-1)
{
}

Mesh::~Mesh()
{
  glDeleteBuffers(1, &m_vbo_positions);
  glDeleteBuffers(1, &m_vbo_texcoords);
  glDeleteBuffers(1, &m_vbo_normals);
  glDeleteBuffers(1, &m_vbo_elements);
  glDeleteVertexArrays(1, &m_vao);
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

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo_positions);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);
  glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(glm::vec3), &m_positions[0], GL_STATIC_DRAW);

  glGenBuffers(1, &m_vbo_texcoords);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_texcoords);
  glBufferData(GL_ARRAY_BUFFER, m_texcoords.size() * sizeof(glm::vec2), &m_texcoords[0], GL_STATIC_DRAW);

  glGenBuffers(1, &m_vbo_normals);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
  glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);

  glGenBuffers(1, &m_vbo_elements);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_elements);
  glBufferData(GL_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned short int), &m_indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_texcoords);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_elements);

  glBindVertexArray(0);
}

void Mesh::render()
{
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, GLsizei(m_indices.size()), GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);
}

}; // glwnd