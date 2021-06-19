/**
 * @file   view.cpp
 * @author Vic P.
 * @brief  GL View
 */

#include "glwnd/view.h"
#include "glwnd/viewport.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

glm::mat4 GLView::transform_matrix(const glm::vec3& t, const glm::vec3& r, const glm::vec3& s, glm::mat4* m)
{
  glm::mat4 mtx = glm::mat4(1.F);
  mtx = mtx\
    * glm::translate(mtx, t)
    * glm::rotate(mtx, r.x, glm::vec3(1.F, 0.F, 0.F)) // X
    * glm::rotate(mtx, r.y, glm::vec3(0.F, 1.F, 0.F)) // Y
    * glm::rotate(mtx, r.z, glm::vec3(0.F, 0.F, 1.F)) // Z
    * glm::scale(mtx, s);

  if (m != nullptr)
  {
    mtx *= *m;
  }

  return mtx;
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