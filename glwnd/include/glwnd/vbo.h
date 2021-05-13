#pragma once

/**
 * @file   vbo.h
 * @author Vic P.
 * @brief  Vertex Buffer Object (VBO)
 */

#include <GL/glew.h>

class VBO
{
public:
  VBO(GLvoid* data_ptr, GLsizei data_size, GLsizei object_size, GLenum usage = GL_STATIC_DRAW);
  virtual ~VBO();

  void declare_data_format(GLuint offset, GLuint object_num_fields, GLenum object_field_type);
  void draw(GLenum mode);

private:
  GLuint m_ptr;
  GLuint m_num_objects;
  GLuint m_idx_attribute;
  GLsizei m_object_size;
};