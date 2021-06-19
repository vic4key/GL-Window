/**
 * @file   view.cpp
 * @author Vic P.
 * @brief  GL View
 */

#include "glwnd/view.h"
#include "glwnd/viewport.h"

#include <glm/gtc/type_ptr.hpp>

namespace glwnd
{

GLView::GLView(const p2f& lt, const p2f& rb, const size_t index)
  : m_ptr_viewport(nullptr), m_index(index)
{
  l = lt.x();
  t = lt.y();
  r = rb.x();
  b = rb.y();
}

GLView::~GLView()
{
}

GLView::GLView(const GLView& right)
{
  *this = right;
}

GLView& GLView::operator=(const GLView& right)
{
  m_index = right.m_index;
  m_ptr_viewport = m_ptr_viewport;
  return *this;
}

void GLView::setup(GLViewPort& viewport, int width, int height)
{
  r4i rect(int(width * l), int(height * t), int(width * r), int(height * b));
  viewport.setup(rect);
  m_ptr_viewport = &viewport;
}

glm::mat4 GLView::get_context_matrix(GLenum type)
{
  glm::mat4 matrix;
  glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(matrix));
  return matrix;
}

void GLView::display()
{
  // DO NOTHING
}

size_t GLView::index() const
{
  return m_index;
}

}; // glwnd