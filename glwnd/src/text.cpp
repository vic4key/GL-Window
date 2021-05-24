/**
 * @file   text.cpp
 * @author Vic P.
 * @brief  Text Render
 */

#include "glwnd/text.h"
#include "glwnd/glwnd.h"
#include "glwnd/utils.h"

#define GLT_IMPLEMENTATION
#include "gltext/gltext.h"

// glwnd_3rd_include(glfreetype/TextRenderer.hpp)
#include "../3rdparty/glfreetype/TextRenderer.hpp"

namespace glwnd
{

/**
 * TextRender
 */

static bool g_gltext_initialized = false;

TextRender::TextRender() : m_ptr_parent(nullptr), m_ptr_text(nullptr)
{
}

TextRender::~TextRender()
{
  gltDeleteText(m_ptr_text);
}

bool TextRender::setup(GLWindow* ptr_parent, const std::string& name, float size)
{
  // TODO: Vic. font_family + font_size not yet implemented. 

  m_ptr_parent = ptr_parent;
  if (m_ptr_parent == nullptr)
  {
    return false;
  }

  if (!g_gltext_initialized)
  {
    gltInit();
    g_gltext_initialized = true;
  }

  m_ptr_text = gltCreateText();
  if (m_ptr_text == nullptr)
  {
    return false;
  }

  return true;
}

void TextRender::draw(
  const std::string& text,
  float x,
  float y,
  glwnd::glcolor_t<float> color,
  eTextAlignment ha,
  eTextAlignment va,
  float scale
)
{
  assert(m_ptr_text != nullptr);

  // convert glwnd coordinate to gltext coordinate. eg. [-1, +1] -> [0, 1]
  x = glwnd::conv_range<float>(-1.F, +1.F, +0.F, +1.F, +x);
  y = glwnd::conv_range<float>(-1.F, +1.F, +0.F, +1.F, -y);

  // translate glwnd alignment to gltext alignment
  const auto glta = [](eTextAlignment ta) -> GLenum
  {
    GLenum result = GLT_CENTER;

    switch (ta)
    {
    case eTextAlignment::ALIGN_TOP:
      result = GLT_TOP;
      break;

    case eTextAlignment::ALIGN_LEFT:
      result = GLT_LEFT;
      break;

    case eTextAlignment::ALIGN_RIGHT:
      result = GLT_RIGHT;
      break;

    case eTextAlignment::ALIGN_BOTTOM:
      result = GLT_BOTTOM;
      break;

    default:
      break;
    }

    return result;
  };

  auto& win = m_ptr_parent->viewport().coordinate().win;
  int w = win.width();
  int h = win.height();

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  gltBeginDraw();
  {
    gltColor(color.r, color.g, color.b, color.a);
    gltSetText(m_ptr_text, text.c_str());
    gltDrawText2DAligned(m_ptr_text, w * x, h * y, scale, glta(ha), glta(va));
  }
  gltEndDraw();
  glPopAttrib();
}

/**
 * TextRender2D
 */

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

bool TextRender2D::initialize(GLWindow* ptr_parent, const std::string& name, const int size)
{
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

  glfreetype::print(*it->second, position.x(), position.y(), text);
}

void TextRender2D::render_text(const std::string& text, const p2d& position, int* ptr_font_id /*= nullptr*/)
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