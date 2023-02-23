#pragma once

/**
 * @file   vao.h
 * @author Vic P.
 * @brief  Vertex Array Object (VAO)
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

class VBO;

class VAO
{
public:
  VAO();
  virtual ~VAO();

  GLuint id() const;
  bool ready() const;

  void setup_begin();
  void setup_end();

  bool declare_mesh_format(const std::vector<vertex_t>& vertices, const std::vector<uint16>& indices);

  bool declare_position_format(const block_t& data, GLuint num, GLenum type);
  bool declare_texcoord_format(const block_t& data, GLuint num, GLenum type);
  bool declare_normal_format(const block_t& data, GLuint num, GLenum type);
  bool declare_index_format(const block_t& data, GLuint num, GLenum type);

  void render(GLenum mode);

private:
  bool m_ready;
  GLuint m_id;
  GLsizei m_num_indices;
  GLenum  m_type_indices;
  std::vector<VBO*> m_vbo_list;
};

}; // glwnd