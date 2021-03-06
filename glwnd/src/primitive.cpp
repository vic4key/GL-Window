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

void GLPrimitive::initialize(GLView* ptr_parent)
{
  assert(ptr_parent != nullptr);

  m_ptr_parent = ptr_parent;
  m_ptr_text_render->initialize(m_ptr_parent);
}

void GLPrimitive::circle(const p2d& center, double radius, circle_t type, int nsegments)
{
  double angle = 0.;
  const double step = 3.1415 * 2. / double(nsegments);

  glBegin(GLuint(type));
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

void GLPrimitive::circle(const p2i& center, int radius, circle_t type, int nsegments)
{
  assert(m_ptr_parent != nullptr);

  auto c = this->viewport().vpc_to_ndc(center);
  auto p = this->viewport().vpc_to_ndc(p2i(center.x() + radius, center.y()));
  auto r = c.distance(p); // TODO: Vic. Temporary. For case viewport width == height, then r.x == r.y

  this->circle(c, r, type, nsegments);
}

void GLPrimitive::line(const p2d& p1, const p2d& p2, line_t type)
{
  if (type == line_t::solid)
  {
    glBegin(GL_LINES);
    {
      glVertex2d(p1.x(), p1.y());
      glVertex2d(p2.x(), p2.y());
    }
    glEnd();
  }
  else
  {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(type == line_t::dot ? 1 : 2, GLushort(type));
    glBegin(GL_LINE_STRIP);
    {
      glVertex2d(p1.x(), p1.y());
      glVertex2d(p2.x(), p2.y());
    }
    glEnd();
    glPopAttrib();
  }
}

void GLPrimitive::line(const p2i& p1, const p2i& p2, line_t type)
{
  assert(m_ptr_parent != nullptr);

  auto p_1 = this->viewport().vpc_to_ndc(p1);
  auto p_2 = this->viewport().vpc_to_ndc(p2);

  this->line(p_1, p_2, type);
}

void GLPrimitive::scatter(const std::initializer_list<p2d>& points)
{
  glBegin(GL_POINTS);
  {
    for (auto& point : points)
    {
      glVertex2d(point.x(), point.y());
    }
  }
  glEnd();
}

void GLPrimitive::scatter(const std::initializer_list<p2i>& points)
{
  assert(m_ptr_parent != nullptr);

  glBegin(GL_POINTS);
  {
    for (const auto& point : points)
    {
      auto p = this->viewport().vpc_to_ndc(point);
      glVertex2d(p.x(), p.y());
    }
  }
  glEnd();
}

TextRender2D& GLPrimitive::text()
{
  return *m_ptr_text_render;
}

}; // glwnd