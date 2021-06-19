/**
 * @file   layout.cpp
 * @author Vic P.
 * @brief  GL Layout
 */

#include "glwnd/layout.h"
#include "glwnd/view.h"

namespace glwnd
{

GLLayout::GLLayout(GLWindow& parent) : m_ptr_parent(&parent)
{
  m_ptr_views.clear();
}

GLLayout::~GLLayout()
{
  this->remove_all_views();
}

GLLayout::GLLayout(const GLLayout& right)
{
  *this = right;
}

GLLayout& GLLayout::operator=(const GLLayout& right)
{
  m_ptr_parent = right.m_ptr_parent;
  m_ptr_views  = right.m_ptr_views;
  return *this;
}

void GLLayout::remove_all_views()
{
  for (auto& ptr_view : m_ptr_views)
  {
    delete ptr_view;
  }
}

void GLLayout::add_view(const p2f& left_bottom, const p2f& top_left)
{
  m_ptr_views.push_back(new GLView(left_bottom, top_left, m_ptr_views.size()));
}

std::vector<GLView*>& GLLayout::views()
{
  return m_ptr_views;
}

std::unique_ptr<GLLayout> GLLayout::_1x1(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(p2f(0.F, 0.F), p2f(1.F, 1.F));
  return result;
}

std::unique_ptr<GLLayout> GLLayout::_1x2(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(p2f(0.0F, 0.0F), p2f(1.0F, 0.5F)); // B
  result->add_view(p2f(0.0F, 0.5F), p2f(1.0F, 1.0F)); // T
  return result;
}

std::unique_ptr<GLLayout> GLLayout::_2x1(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(p2f(0.0F, 0.0F), p2f(0.5F, 1.0F)); // L
  result->add_view(p2f(0.5F, 0.0F), p2f(1.0F, 1.0F)); // R
  return result;
}

std::unique_ptr<GLLayout> GLLayout::_2x2(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(p2f(0.0F, 0.0F), p2f(0.5F, 0.5F)); // BL
  result->add_view(p2f(0.5F, 0.0F), p2f(1.0F, 0.5F)); // BR
  result->add_view(p2f(0.0F, 0.5F), p2f(0.5F, 1.0F)); // TL
  result->add_view(p2f(0.5F, 0.5F), p2f(1.0F, 1.0F)); // TR
  return result;
}

}; // glwnd