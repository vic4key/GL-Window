/**
 * @file   vbo.cpp
 * @author Vic P.
 * @brief  Vertex Buffer Object (VBO)
 */

#include "glwnd/vbo.h"

#include <cassert>

#pragma warning(disable : 4312)

namespace glwnd
{

static auto gl_sizeof_type= [](GLenum type) -> GLuint
{
  GLuint result = 0;

  switch (type)
  {
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:
    result = 1;
    break;

  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
  case GL_2_BYTES:
    result = 2;
    break;

  case GL_INT:
  case GL_UNSIGNED_INT:
  case GL_FLOAT:
  case GL_4_BYTES:
    result = 4;
    break;

  case GL_3_BYTES:
    result = 3;
    break;

  case GL_DOUBLE:
    result = 8;
    break;

  default:
    break;
  }

  return result;
};

VBO::VBO(GLvoid* data_ptr, GLsizei data_size, GLsizei vds_size, GLenum usage)
  : m_id(0), m_vds_size(vds_size), m_binded(false)
{
  // calculate number of elements in the data block
  m_num_elements = data_size / vds_size;

  // allocate memory in GPU
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);

  // send and store data to GPU
  glBufferData(GL_ARRAY_BUFFER, data_size, data_ptr, usage);

  // verify the stored data size is the sane as the sent data size
  GLsizei stored_data_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &stored_data_size);
  assert(data_size == stored_data_size);
}

VBO::~VBO()
{
  // disable used states
  for (auto& state : m_used_client_states)
  {
    glDisableClientState(state);
  }

  // free the allocated memory in GPU
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_id);
}

void VBO::bind()
{
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

  return num * gl_sizeof_type(type);
}

GLuint VBO::declare_color_format(GLuint offset, GLuint num, GLenum type, GLuint stride)
{
  this->bind();
  this->enable_client_state(GL_COLOR_ARRAY);

  glColorPointer(num, type, stride, reinterpret_cast<GLvoid*>(offset));

  return num * gl_sizeof_type(type);
}

GLuint VBO::declare_texture_format(GLuint offset, GLuint num, GLenum type, GLuint stride)
{
  this->bind();
  this->enable_client_state(GL_TEXTURE_COORD_ARRAY);

  glClientActiveTexture(GL_TEXTURE0);

  glTexCoordPointer(num, type, stride, reinterpret_cast<GLvoid*>(offset));

  return num * gl_sizeof_type(type);
}

GLuint VBO::declare_normal_format(GLuint offset, GLuint num, GLenum type, GLuint stride)
{
  this->bind();
  this->enable_client_state(GL_NORMAL_ARRAY);

  glNormalPointer(type, stride, reinterpret_cast<GLvoid*>(offset));

  return num * gl_sizeof_type(type);
}

}; // glwnd