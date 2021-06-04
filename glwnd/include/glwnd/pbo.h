#pragma once

/**
 * @file   pbo.h
 * @author Vic P.
 * @brief  Pixel Buffer Object (PBO)
 */

#include <gl/glew.h>
#include <functional>
#include <string>

#include "defs.h"

namespace glwnd
{

class PBO
{
public:
  PBO();
  virtual ~PBO();

  GLWND_DELETE_UNUSED_OPERATORS(PBO)

  bool initialize_from_image_file(const std::string& file_path);
  bool initialize(GLvoid* ptr_pixel_data, int width, int height, int channel, GLint iformat, GLint format);
  bool use();

private:
  bool unpack();
  bool pack(std::function<void(const void* ptr)> fn);

private:
  GLuint  m_id;
  bool    m_ready;
  int     m_width;
  int     m_height;
  int     m_channel;
  GLint   m_iformat;
  GLint   m_format;
  GLvoid* m_ptr_pixels;
};

}; // glwnd