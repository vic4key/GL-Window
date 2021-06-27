/**
 * @file   text.cpp
 * @author Vic P.
 * @brief  Text Render 2D
 */

#include "glwnd/text.h"
#include "glwnd/view.h"
#include "glwnd/viewport.h"

#include "glfreetype/TextRenderer.hpp"

namespace glwnd
{

TextRender2D::TextRender2D() : m_ptr_parent(nullptr), m_current_font_id(INVALID_FONT_ID)
{
  m_fonts.clear();
}

TextRender2D::~TextRender2D()
{
  for (auto& font : m_fonts)
  {
    font.second->clean();
    delete font.second;
  }
}

bool TextRender2D::initialize(GLView* ptr_parent, const std::string& name, const int size)
{
  assert(ptr_parent != nullptr);

  if (!m_fonts.empty())
  {
    return true;
  }

  m_ptr_parent = ptr_parent;

  return this->add_font(name, size) != INVALID_FONT_ID;
}

int TextRender2D::add_font(const std::string& name, const int size)
{
  auto ptr_font = new glfreetype::font_data;

  try
  {
    ptr_font->init(name.c_str(), size);
  }
  catch (...)
  {
    delete ptr_font;
    ptr_font = nullptr;
  }

  if (ptr_font == nullptr)
  {
    return INVALID_FONT_ID;
  }

  m_fonts[++m_current_font_id] = ptr_font;

  return m_current_font_id;
}

void TextRender2D::render_text(const std::string& text, const p2i& position, int* ptr_font_id)
{
  assert(!m_fonts.empty());

  int font_id = ptr_font_id != nullptr ? *ptr_font_id : 0; // 0 is the font id in the setup time
  auto it = m_fonts.find(font_id);
  assert(it != m_fonts.cend());

  assert(m_ptr_parent != nullptr);
  const auto& win = m_ptr_parent->viewport().coordinate().win;

  glfreetype::print(
    win.left(), win.right(), win.bottom(), win.top(), *it->second, position.x(), position.y(), text);
}

void TextRender2D::render_text(const std::string& text, const p2d& position, int* ptr_font_id)
{
  assert(m_ptr_parent != nullptr);
  auto p = m_ptr_parent->viewport().ndc_to_win(position);
  this->render_text(text, p, ptr_font_id);
}

size_t TextRender2D::get_num_added_fonts()
{
  return m_fonts.size();
}

}; // glwnd