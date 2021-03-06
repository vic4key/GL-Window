/**
 * @file   layout.cpp
 * @author Vic P.
 * @brief  GL Layout
 */

#include "glwnd/layout.h"
#include "glwnd/view.h"
#include "glwnd/utils.h"

#include <cassert>

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

std::vector<GLView*>& GLLayout::views()
{
  return m_ptr_views;
}

GLLayout& GLLayout::add_view(GLView* ptr_view)
{
  assert(ptr_view != nullptr);

  ptr_view->set_parent(*m_ptr_parent);
  ptr_view->set_index(m_ptr_views.size());

  m_ptr_views.push_back(ptr_view);

  return *this;
}

GLLayout& GLLayout::replace_view(GLView* ptr_view, size_t index)
{
  assert(ptr_view != nullptr && index >= 0 && index < m_ptr_views.size());

  auto& e = m_ptr_views[index];

  *ptr_view = *m_ptr_views[index];
  delete m_ptr_views[index];

  m_ptr_views[index] = ptr_view;

  return *this;
}

GLLayout& GLLayout::remove_all_views()
{
  for (auto& ptr_view : m_ptr_views)
  {
    if (ptr_view != nullptr)
    {
      delete ptr_view;
    }
  }

  m_ptr_views.clear();

  return *this;
}

GLView* GLLayout::get_active_view_from_mouse_position(const p2i& point)
{
  GLView* result = nullptr;

  for (auto& ptr_view : m_ptr_views)
  {
    const auto& win = ptr_view->viewport().coordinate().win;
    if (utils::is_point_inside_rect(point, win))
    {
      result = ptr_view;
      break;
    }
  }

  return result;
}

std::unique_ptr<GLLayout> GLLayout::_empty(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  // no any view
  return result;
}

std::unique_ptr<GLLayout> GLLayout::_1x1(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(new GLViewDefault(p2f(0.F, 0.F), p2f(1.F, 1.F)));
  return result;
}

std::unique_ptr<GLLayout> GLLayout::_1x2(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(new GLViewDefault(p2f(0.0F, 0.0F), p2f(1.0F, 0.5F))); // B
  result->add_view(new GLViewDefault(p2f(0.0F, 0.5F), p2f(1.0F, 1.0F))); // T
  return result;
}

std::unique_ptr<GLLayout> GLLayout::_2x1(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(new GLViewDefault(p2f(0.0F, 0.0F), p2f(0.5F, 1.0F))); // L
  result->add_view(new GLViewDefault(p2f(0.5F, 0.0F), p2f(1.0F, 1.0F))); // R
  return result;
}

std::unique_ptr<GLLayout> GLLayout::_2x2(GLWindow& parent)
{
  std::unique_ptr<GLLayout> result(new GLLayout(parent));
  result->add_view(new GLViewDefault(p2f(0.0F, 0.0F), p2f(0.5F, 0.5F))); // BL
  result->add_view(new GLViewDefault(p2f(0.5F, 0.0F), p2f(1.0F, 0.5F))); // BR
  result->add_view(new GLViewDefault(p2f(0.0F, 0.5F), p2f(0.5F, 1.0F))); // TL
  result->add_view(new GLViewDefault(p2f(0.5F, 0.5F), p2f(1.0F, 1.0F))); // TR
  return result;
}

}; // glwnd