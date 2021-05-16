#pragma once

/**
 * @file   vbo.h
 * @author Vic P.
 * @brief  Vertex Buffer Object (VBO)
 */

#include <GL/glew.h>

#include <vector>

namespace glwnd
{

class VBO
{
public:
  VBO(GLvoid* data_ptr, GLsizei data_size, GLsizei group_size, GLenum usage = GL_STATIC_DRAW);
  virtual ~VBO();

  void declare_vertex_format(GLuint offset, GLuint num_elements, GLenum element_type, GLuint* ptr_next_offset = nullptr);
  void declare_color_format(GLuint offset, GLuint num_elements, GLenum element_type, GLuint* ptr_next_offset = nullptr);
  void declare_texture_format(GLuint offset, GLuint num_elements, GLenum element_type, GLuint* ptr_next_offset = nullptr);
  void declare_normal_format(GLuint offset, GLuint num_elements, GLenum element_type, GLuint* ptr_next_offset = nullptr);

  void draw(GLenum mode);

private:
  void bind();
  void enable_client_state(GLenum state);

private:
  bool    m_binded;
  GLuint  m_id;
  GLuint  m_num_groups;
  GLsizei m_group_size;
  std::vector<GLuint> m_used_client_states;
};

}; // glwnd