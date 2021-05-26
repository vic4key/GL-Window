/**
 * @file   primitive.cpp
 * @author Vic P.
 * @brief  Rendering Primitives
 */

#include "glwnd/primitive.h"
#include "glwnd/viewport.h"
#include "glwnd/text.h"
#include "glwnd/glwnd.h"

#include <gl/glew.h>

namespace glwnd
{

GLPrimitive::GLPrimitive()
{
  m_ptr_text_render = new TextRender2D;
}

GLPrimitive::~GLPrimitive()
{
  delete m_ptr_text_render;
}

void GLPrimitive::initialize(GLWindow* ptr_parent)
{
  assert(ptr_parent != nullptr);

  m_ptr_parent = ptr_parent;
  m_ptr_text_render->initialize(m_ptr_parent);
}

void GLPrimitive::circle(const p2d& center, double radius, bool fill, int nsegments)
{
  double angle = 0.;
  const double step = 3.1415 * 2. / double(nsegments);

  glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
  {
    for (int i = 0; i < nsegments; i++)
    {
      double x = std::sin(angle) * radius + center.x();
      double y = std::cos(angle) * radius + center.y();
      glVertex2d(x, y);
      angle += step;
    }
  }
  glEnd();
}

void GLPrimitive::circle(const p2i& center, int radius, bool fill, int nsegments)
{
  assert(0);
}

void GLPrimitive::line(const p2d& p1, const p2d& p2)
{
  glBegin(GL_LINES);
  {
    glVertex2d(p1.x(), p1.y());
    glVertex2d(p2.x(), p2.y());
  }
  glEnd();
}

void GLPrimitive::line(const p2i& p1, const p2i& p2)
{
  assert(0);
}

TextRender2D& GLPrimitive::text()
{
  return *m_ptr_text_render;
}

}; // glwnd