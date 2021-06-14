/**
 * @file   pbo.cpp
 * @author Vic P.
 * @brief  Pixel Buffer Object (PBO)
 */

#include "glwnd/pbo.h"
#include "glwnd/defs.h"
#include "glwnd/utils.h"

#include <SOIL2/SOIL2.h>
#include <cassert>
#include <cstring>

namespace glwnd
{

PBO::PBO()
  : m_ready(false)
  , m_id(GL_INVALID_ID)
  , m_format(0)
  , m_ptr_pixels(nullptr), m_width(0), m_height(0), m_channel(0), m_iformat(0)
{
}

PBO::~PBO()
{
  if (m_id != GL_INVALID_ID)
  {
    // release memory after used
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // deallocate the buffer memory in GPU
    glDeleteBuffers(1, &m_id);
  }
}

bool PBO::initialize_from_image_file(const std::string& file_path)
{
  bool result = false;

  int width = 0;
  int height = 0;
  int channel = 0;
  auto ptr_pixels = SOIL_load_image(file_path.c_str(), &width, &height, &channel, SOIL_LOAD_AUTO);
  if (ptr_pixels != nullptr)
  {
    GLint format  = GL_RGBA;
    GLint iformat = GL_RGBA8;
    utils::image_channel_to_format_types(channel, iformat, format);

    result = this->initialize(ptr_pixels, width, height, channel, iformat, format);

    SOIL_free_image_data(ptr_pixels);
  }

  return result;
}

bool PBO::initialize(GLvoid* ptr_pixels, int width, int height, int channel, GLint iformat, GLint format)
{
  if (m_ready)
  {
    return true;
  }

  // declare a buffer memory in GPU
  if (m_id == GL_INVALID_ID)
  {
    glGenBuffers(1, &m_id);
  }

  m_format = format;

  m_ptr_pixels = ptr_pixels;
  m_width   = width;
  m_height  = height;
  m_channel = channel;
  m_iformat = iformat;

  return this->unpack();
}

bool PBO::use()
{
  if (!m_ready)
  {
    return false;
  }

  return this->pack([&](const void* ptr)
  {
    ::glTexImage2D(
      GL_TEXTURE_2D,
      0,
      m_iformat,
      m_width,
      m_height,
      0,
      m_format,
      GL_UNSIGNED_BYTE,
      ptr
    );
  });
}

bool PBO::unpack()
{
  if (m_ptr_pixels == nullptr || m_width <= 0 || m_height <= 0 || m_channel <= 0)
  {
    return false;
  }

  int size = m_width * m_height * m_channel;

  // bind a buffer for using
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_id);

  // PBO allocate a DMA buffer in GPU, this is a kind of fast memory access named DMA (Direct Memory Access)
  glBufferData(GL_PIXEL_UNPACK_BUFFER, size, nullptr, GL_STREAM_DRAW);

  // map the allocated DMA buffer as a writable buffer
  void* ptr_mapped_buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);

  // store the pixel data into the mapped writable PBO buffer in GPU
  memcpy(ptr_mapped_buffer, m_ptr_pixels, size);

  // unmap the buffer after copied
  glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

  // unbind the buffer data after used
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

  // clear the 2d texture image buffer
  // glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_display_format, GL_UNSIGNED_BYTE, nullptr);

  m_ready = true;

  return true;
}

bool PBO::pack(std::function<void(const void* ptr)> fn)
{
  if (!m_ready || m_ptr_pixels == nullptr || m_width <= 0 || m_height <= 0 || m_channel <= 0)
  {
    return false;
  }

  // bind a buffer for using
  glBindBuffer(GL_PIXEL_PACK_BUFFER, m_id);

  // PBO access to the allocated DMA buffer that stored the pixel data before
  glGetTexImage(GL_TEXTURE_2D, 0, m_iformat, GL_UNSIGNED_BYTE, nullptr);

  // map the accessed DMA buffer as a read-only buffer
  void* ptr_mapped_buffer = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

  // call an operation to use the pixel data as 2d texture image
  fn(ptr_mapped_buffer);

  // unmap the buffer after copied
  glUnmapBuffer(GL_PIXEL_PACK_BUFFER);

  // unbind the buffer data after used
  glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

  return true;
}

}; // glwnd