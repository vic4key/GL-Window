/**
 * @file   tex2d.cpp
 * @author Vic P.
 * @brief  Texture 2D
 */

#include "glwnd/tex2d.h"

#include <SOIL2/SOIL2>
#include <cassert>

namespace glwnd
{

Tex2D::Tex2D(GLint wrap, GLint filter) : m_wrap(wrap), m_filter(filter), m_initialized(false)
{
  glGenTextures(1, &m_id);
}

Tex2D::~Tex2D()
{
  glDeleteTextures(1, &m_id);
}

void Tex2D::use(bool state)
{
  if (state)
  {
    this->bind();
  }
  else
  {
    this->unbind();
  }
}

void Tex2D::bind()
{
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void Tex2D::unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

bool Tex2D::init_from_image_file(const std::string& file_path)
{
  if (m_initialized)
  {
    return true;
  }

  bool result = false;

  int width = 0;
  int height = 0;
  int channel = 0;
  auto ptr_pixels = SOIL_load_image(file_path.c_str(), &width, &height, &channel, SOIL_LOAD_AUTO);
  if (ptr_pixels != nullptr)
  {
    GLint format = GL_RGBA;
    GLint internal_format = GL_RGBA8;

    switch (channel)
    {
    case 1: // gray
      format = GL_LUMINANCE;
      internal_format = GL_LUMINANCE8;
      break;

    case 3: // rgb
      format = GL_RGB;
      internal_format = GL_RGB8;
      break;

    case 4: // rgba
      format = GL_RGBA;
      internal_format = GL_RGBA8;
      break;

    default:
      break;
    }

    result = this->init(width, height, ptr_pixels, internal_format, format);
  }

  SOIL_free_image_data(ptr_pixels);

  return result;
}

bool Tex2D::init(GLsizei width, GLsizei height, GLvoid* ptr_pixels, GLint iformat, GLenum format)
{
  if (m_initialized)
  {
    return true;
  }

  assert(width != 0 && height != 0 && ptr_pixels != nullptr);

  this->use(true);
  {
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4

    glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, ptr_pixels);
  }
  this->use(false);

  m_initialized = true;

  return true;
}

}; // glwnd