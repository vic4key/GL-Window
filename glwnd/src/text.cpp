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

static bool g_gltext_initialized = false;

TextRender::TextRender() : m_ptr_parent(nullptr), m_ptr_text(nullptr)
{
}

TextRender::~TextRender()
{
  gltDeleteText(m_ptr_text);
}

bool TextRender::setup(GLWindow* ptr_parent)
{
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

  const int w = m_ptr_parent->width();
  const int h = m_ptr_parent->height();

  glPushClientAttrib(GL_ALL_ATTRIB_BITS);
  gltBeginDraw();
  {
    gltColor(color.r, color.g, color.b, color.a);
    gltSetText(m_ptr_text, text.c_str());
    gltDrawText2DAligned(m_ptr_text, w * x, h * y, scale, glta(ha), glta(va));
  }
  gltEndDraw();
  glPopClientAttrib();
}