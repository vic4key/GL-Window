/**
 * @file   vao.cpp
 * @author Vic P.
 * @brief  Vertex Array Object (VAO)
 */

#include "glwnd/vao.h"
#include "glwnd/defs.h"
#include "glwnd/utils.h"

#include "glwnd/vbo.h"

#include <cassert>

#pragma warning(disable : 4312)

namespace glwnd
{

VAO::VAO() : m_ready(false), m_id(GL_INVALID_ID), m_num_indices(0), m_type_indices(GL_INVALID_ENUM)
{
}

VAO::~VAO()
{
  if (!m_ready)
  {
    return;
  }

  for (auto& ptr_vbo : m_vbo_list)
  {
    if (ptr_vbo != nullptr)
    {
      delete ptr_vbo;
    }
  }

  if (m_id != GL_INVALID_ID)
  {
    glDeleteVertexArrays(1, &m_id);
  }

  glBindVertexArray(0);
}

GLuint VAO::id() const
{
  return m_id;
}

bool VAO::ready() const
{
  return m_ready;
}

void VAO::setup_begin()
{
  assert(!m_ready && "VAO was setup");

  glGenVertexArrays(1, &m_id);
  glBindVertexArray(m_id);

  m_ready = true;
}

void VAO::setup_end()
{
  glBindVertexArray(0);
}

bool VAO::declare_position_format(const block_t& data, GLuint num, GLenum type)
{
  assert(m_ready && "VAO - not yet setup");

  m_vbo_list.emplace_back(new VBO);
  auto ptr_vbo = m_vbo_list.back();
  assert(ptr_vbo != nullptr && "VAO - create vbo for position format failed");

  GLuint vds_size = num * utils::gl_sizeof_type(type);
  bool succeed = ptr_vbo->setup_begin(data.ptr, data.size, vds_size);
  {
    GLuint attrib_index = GLuint(m_vbo_list.size() - 1);
    glEnableVertexAttribArray(attrib_index);
    glBindBuffer(GL_ARRAY_BUFFER, ptr_vbo->id());
    glVertexAttribPointer(attrib_index, num, type, GL_FALSE, 0, 0);
  }
  ptr_vbo->setup_end();

  return succeed;
}

bool VAO::declare_texcoord_format(const block_t& data, GLuint num, GLenum type)
{
  assert(m_ready && "VAO - not yet setup");

  m_vbo_list.emplace_back(new VBO);
  auto ptr_vbo = m_vbo_list.back();
  assert(ptr_vbo != nullptr && "VAO - create vbo for texcoord format failed");

  GLuint vds_size = num * utils::gl_sizeof_type(type);
  bool succeed = ptr_vbo->setup_begin(data.ptr, data.size, vds_size);
  {
    GLuint attrib_index = GLuint(m_vbo_list.size() - 1);
    glEnableVertexAttribArray(attrib_index);
    glBindBuffer(GL_ARRAY_BUFFER, ptr_vbo->id());
    glVertexAttribPointer(attrib_index, num, type, GL_FALSE, 0, 0);
  }
  ptr_vbo->setup_end();

  return succeed;
}

bool VAO::declare_normal_format(const block_t& data, GLuint num, GLenum type)
{
  assert(m_ready && "VAO - not yet setup");

  m_vbo_list.emplace_back(new VBO);
  auto ptr_vbo = m_vbo_list.back();
  assert(ptr_vbo != nullptr && "VAO - create vbo for normal format failed");

  GLuint vds_size = num * utils::gl_sizeof_type(type);
  bool succeed = ptr_vbo->setup_begin(data.ptr, data.size, vds_size);
  {
    GLuint attrib_index = GLuint(m_vbo_list.size() - 1);
    glEnableVertexAttribArray(attrib_index);
    glBindBuffer(GL_ARRAY_BUFFER, ptr_vbo->id());
    glVertexAttribPointer(attrib_index, num, type, GL_FALSE, 0, 0);
  }
  ptr_vbo->setup_end();

  return succeed;
}

bool VAO::declare_index_format(const block_t& data, GLuint num, GLenum type)
{
  assert(m_ready && "VAO - not yet setup");

  m_vbo_list.emplace_back(new VBO);
  auto ptr_vbo = m_vbo_list.back();
  assert(ptr_vbo != nullptr && "VAO - create vbo for index format failed");

  GLuint vds_size = num * utils::gl_sizeof_type(type);
  bool succeed = ptr_vbo->setup_begin(data.ptr, data.size, vds_size);
  {
    GLuint attrib_index = GLuint(m_vbo_list.size() - 1);
    glEnableVertexAttribArray(attrib_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ptr_vbo->id());
    glVertexAttribPointer(attrib_index, num, type, GL_FALSE, 0, 0);
  }
  ptr_vbo->setup_end();

  m_num_indices  = data.size / vds_size;
  m_type_indices = type;

  return succeed;
}

void VAO::render(GLenum mode)
{
  assert(m_ready && "VAO - not yet setup");
  assert((m_num_indices > 0 && m_type_indices != GL_INVALID_ENUM) && "VAO - invalid indices");

  glBindVertexArray(m_id);
  {
    glDrawElements(mode, m_num_indices, m_type_indices, 0);
  }
  glBindVertexArray(0);
}

}; // glwnd