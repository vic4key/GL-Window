/**
 * @file   vbo.cpp
 * @author Vic P.
 * @brief  Vertex Buffer Object (VBO)
 */

#include "glwnd/vbo.h"

#pragma warning(disable : 4312)

VBO::VBO(GLvoid* data_ptr, GLsizei data_size, GLsizei object_size, GLenum usage)
  : m_ptr(0), m_idx_attribute(-1), m_object_size(object_size)
{
  // calculate number of elements
  m_num_objects = data_size / object_size;

  // allocate memory in GPU
  glGenBuffers(1, &m_ptr);
  glBindBuffer(GL_ARRAY_BUFFER, m_ptr);

  // send and store vertices to GPU
  glBufferData(GL_ARRAY_BUFFER, data_size, data_ptr, usage);
}

void VBO::declare_data_format(GLuint offset, GLuint object_num_fields, GLenum object_field_type)
{
  // use attributes to specify location and format of the data
  glEnableVertexAttribArray(++m_idx_attribute);
  glVertexAttribPointer(
    m_idx_attribute,
    object_num_fields,
    object_field_type,
    GL_FALSE,
    m_object_size,
    reinterpret_cast<const void*>(offset)
  );
}

VBO::~VBO()
{
  // free used attributes
  for (GLuint i = 0; i <= m_idx_attribute; i++)
  {
    glDisableVertexAttribArray(i);
  }

  // free the allocated memory in GPU
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_ptr);
}

void VBO::draw(const GLenum mode)
{
  glDrawArrays(mode, 0, m_num_objects);
}