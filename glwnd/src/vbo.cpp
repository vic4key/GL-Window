/**
 * @file   vbo.cpp
 * @author Vic P.
 * @brief  Vertex Buffer Object (VBO)
 */

#include "glwnd/vbo.h"
#include "glwnd/defs.h"
#include "glwnd/utils.h"

#include <cassert>

#pragma warning(disable : 4312)

namespace glwnd
{

VBO::VBO()
  : m_id(GL_INVALID_ID), m_num_elements(0), m_vds_size(0), m_binded(false)
{
}

VBO::VBO(GLvoid* data_ptr, GLsizei data_size, GLsizei vds_size, GLenum usage)
  : m_id(GL_INVALID_ID), m_vds_size(vds_size), m_binded(false)
{
  this->initialize(data_ptr, data_size, vds_size, usage);
}

VBO::~VBO()
{
  // disable used states
  for (auto& state : m_used_client_states)
  {
    glDisableClientState(state);
  }

  if (m_id != GL_INVALID_ID)
  {
    // release memory after used
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // deallocate the buffer memory in GPU
    glDeleteBuffers(1, &m_id);
  }
}

bool VBO::initialize(const GLvoid* data_ptr, GLsizei data_size, GLsizei vds_size, GLenum usage)
{
  // declare a buffer memory in GPU
  if (m_id == GL_INVALID_ID)
  {
    glGenBuffers(1, &m_id);
  }

  this->bind();

  // allocate memory in GPU then send data from app to store into GPU
  glBufferData(GL_ARRAY_BUFFER, data_size, data_ptr, usage);

  // calculate number of elements in the data block
  m_num_elements = data_size / vds_size;

  // verify the stored data size is the sane as the sent data size
  GLsizei stored_data_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &stored_data_size);

  return data_size == stored_data_size;
}

bool VBO::initialize(const std::initializer_list<block_t>& data_list, GLsizei vds_size, GLenum usage)
{
  // declare a buffer memory in GPU
  if (m_id == GL_INVALID_ID)
  {
    glGenBuffers(1, &m_id);
  }

  this->bind();

  // calculate total data size in the data list
  GLsizei data_size = 0;
  for (auto& e : data_list)
  {
    data_size += e.size;
  }

  // allocate memory in GPU
  glBufferData(GL_ARRAY_BUFFER, data_size, nullptr, usage);

  // send data list from app to store into GPU
  GLsizei data_offset = 0;
  for (auto& e : data_list)
  {
    glBufferSubData(GL_ARRAY_BUFFER, data_offset, e.size, e.ptr);
    data_offset += e.size;
  }

  // calculate number of elements in the data block
  m_num_elements = data_size / vds_size;

  // verify the stored data size is the sane as the sent data size
  GLsizei stored_data_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &stored_data_size);

  return data_size == stored_data_size;
}

void VBO::bind()
{
  if (m_id == GL_INVALID_ID)
  {
    assert(0 && "invalid buffer id");
  }

  if (!m_binded)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    m_binded = true;
  }
}

void VBO::enable_client_state(GLenum state)
{
  glEnableClientState(state);
  m_used_client_states.push_back(state);
}

void VBO::draw(const GLenum mode)
{
  this->bind();
  glDrawArrays(mode, 0, m_num_elements);
}

GLuint VBO::get_num_elements() const
{
  return m_num_elements;
}

GLuint VBO::declare_position_format(GLuint offset, GLuint num, GLenum type, GLuint stride)
{
  this->bind();
  this->enable_client_state(GL_VERTEX_ARRAY);

  glVertexPointer(num, type, stride, reinterpret_cast<GLvoid*>(offset));

  return num * utils::gl_sizeof_type(type);
}

GLuint VBO::declare_color_format(GLuint offset, GLuint num, GLenum type, GLuint stride)
{
  this->bind();
  this->enable_client_state(GL_COLOR_ARRAY);

  glColorPointer(num, type, stride, reinterpret_cast<GLvoid*>(offset));

  return num * utils::gl_sizeof_type(type);
}

GLuint VBO::declare_texture_format(GLuint offset, GLuint num, GLenum type, GLuint stride)
{
  this->bind();
  this->enable_client_state(GL_TEXTURE_COORD_ARRAY);

  glClientActiveTexture(GL_TEXTURE0);

  glTexCoordPointer(num, type, stride, reinterpret_cast<GLvoid*>(offset));

  return num * utils::gl_sizeof_type(type);
}

GLuint VBO::declare_normal_format(GLuint offset, GLuint num, GLenum type, GLuint stride)
{
  this->bind();
  this->enable_client_state(GL_NORMAL_ARRAY);

  glNormalPointer(type, stride, reinterpret_cast<GLvoid*>(offset));

  return num * utils::gl_sizeof_type(type);
}

}; // glwnd