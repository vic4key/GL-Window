#pragma once

/**
 * @file   vbo.h
 * @author Vic P.
 * @brief  Vertex Buffer Object (VBO)
 */

#include <GL/glew.h>

#include <vector>

/**
 * Vertex Data Structure aka VDS - a data structure stored any/all of the following attributes:
 *  - position
 *  - color
 *  - texture
 *  - normal
 *  - etc
 */

namespace glwnd
{

class VBO
{
public:
  VBO(GLvoid* data_ptr, GLsizei data_size, GLsizei vds_size, GLenum usage = GL_STATIC_DRAW);
  virtual ~VBO();

  GLuint declare_position_format(GLuint offset, GLuint num, GLenum type, GLuint stride);
  GLuint declare_color_format(GLuint offset, GLuint num, GLenum type, GLuint stride);
  GLuint declare_texture_format(GLuint offset, GLuint num, GLenum type, GLuint stride);
  GLuint declare_normal_format(GLuint offset, GLuint num, GLenum type, GLuint stride);

  void draw(GLenum mode);

  GLuint get_num_elements() const;

private:
  void bind();
  void enable_client_state(GLenum state);

private:
  bool    m_binded;
  GLuint  m_id;
  GLsizei m_vds_size;
  GLuint  m_num_elements;
  std::vector<GLuint> m_used_client_states;
};

}; // glwnd