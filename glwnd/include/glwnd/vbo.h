#pragma once

/**
 * @file   vbo.h
 * @author Vic P.
 * @brief  Vertex Buffer Object (VBO)
 */

#include <gl/glew.h>
#include <vector>
#include <initializer_list>

#include "defs.h"

/**
 * VERTEX DATA STRUCTURE aka VDS - a data structure stored any/all of the following attributes:
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

  // Note parameters for VDS data block
  //  data_ptr - the pointer of VDS data block
  //  data_ptr - the size of VDS data block
  //  vds_size - the size of an element or that is total size of all attributes in a VDS
  //  usage    - define that how the buffer object is going to be used

  VBO();
  VBO(GLvoid* data_ptr, GLsizei data_size, GLsizei vds_size, GLenum usage = GL_STATIC_DRAW);
  virtual ~VBO();

  GLWND_DELETE_UNUSED_OPERATORS(VBO)

  GLuint id() const;

  bool initialize(
    const GLvoid* data_ptr,
    GLsizei data_size,
    GLsizei vds_size,
    GLenum usage = GL_STATIC_DRAW,
    GLenum target = GL_ARRAY_BUFFER);

  bool initialize(
    const std::initializer_list<block_t>& data_list,
    GLsizei vds_size,
    GLenum usage = GL_STATIC_DRAW,
    GLenum target = GL_ARRAY_BUFFER);

  // Note parameters for AN ATTRIBUTE in VDS
  //  offset - the start offset
  //  num    - the number of elements (eg. 2f, 3f, etc)
  //  type   - the data type of an element (eg. 2f, 2d, 3f, 3d, etc)
  //  stride - the distance in bytes between the offset of current and next element (eg. p[0]->p[1], c[0]->c[1], etc)

  GLuint declare_position_format(GLuint offset, GLuint num, GLenum type, GLuint stride = 0);
  GLuint declare_color_format(GLuint offset, GLuint num, GLenum type, GLuint stride = 0);
  GLuint declare_normal_format(GLuint offset, GLuint num, GLenum type, GLuint stride = 0);
  GLuint declare_texture_format(GLuint offset, GLuint num, GLenum type, GLuint stride = 0);

  void render(GLenum mode);

  GLuint get_num_elements() const;

private:
  void initialize_buffer(GLenum target);
  void enable_client_state(GLenum state);

private:
  bool    m_ready;
  GLuint  m_id;
  GLsizei m_vds_size;
  GLuint  m_num_elements;
  std::vector<GLuint> m_used_client_states;
};

}; // glwnd