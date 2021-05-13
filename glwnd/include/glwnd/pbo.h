#pragma once

/**
 * @file   pbo.h
 * @author Vic P.
 * @brief  Pixel Buffer Object (PBO)
 */

#include <GL/glew.h>

#include <functional>

class PBO
{
public:
  PBO();
  virtual ~PBO();

  bool setup(GLvoid* ptr_pixel_data, int width, int height, int channel, GLint image_format, GLint display_format);
  bool TexImage2D();

private:
  bool unpack();
  bool pack(std::function<void(const void* ptr)> fn);

private:
  bool m_ready;
  GLuint m_id;
  GLint m_display_format;
  GLvoid* m_ptr_pixel_data;
  int m_width;
  int m_height;
  int m_channel;
  GLint m_format;
};