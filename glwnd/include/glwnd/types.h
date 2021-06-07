#pragma once

/**
 * @file   types.h
 * @author Vic P.
 * @brief  Data Types
 */

#include <string>
#include <vector>

namespace glwnd
{

typedef unsigned char  byte_t;
typedef unsigned short word_t;
typedef unsigned int   dword_t;

struct color_t
{
  union
  {
    dword_t rgba;
    struct
    {
      byte_t r, g, b, a;
    };
  };

  color_t(dword_t color) : rgba(color) {};

  color_t(byte_t _r, byte_t _g, byte_t _b, byte_t _a = 0xFF) : r(_r), g(_g), b(_b), a(_a) {};

  color_t& operator=(dword_t color)
  {
    rgba = color;
  }

  color_t& operator=(const color_t& color)
  {
    rgba = color.rgba;
  }
};

template <typename T>
struct glcolor_t
{
  T r;
  T g;
  T b;
  T a;

  glcolor_t(T _r, T _g, T _b, T _a = T(1)) : r(_r), g(_g), b(_b), a(_a) {};

  glcolor_t(const dword_t& color)
  {
    (*this) = glcolor_t(color_t(color));
  }

  glcolor_t(const color_t& color)
  {
    (*this) = color;
  }

  glcolor_t(const glcolor_t& color)
  {
    (*this) = color;
  }

  glcolor_t& operator=(const dword_t& color)
  {
    (*this) = color_t(color);
    return (*this);
  }

  glcolor_t& operator=(const color_t& color)
  {
    r = color.r / T(0xFF);
    g = color.g / T(0xFF);
    b = color.b / T(0xFF);
    a = color.a / T(0xFF);
    return (*this);
  }

  glcolor_t& operator=(const glcolor_t& color)
  {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return (*this);
  }
};

typedef glcolor_t<float>  glcolorf;
typedef glcolor_t<double> glcolord;

struct block_t
{
  void* ptr;
  int   size;

  block_t() : ptr(nullptr), size(0) {}
  block_t(void* p, int z) : ptr(p), size(z) {}
};

struct dear_imgui_cfg
{
  enum class styles
  {
    IMGUI_DARK,
    IMGUI_CLASSIC,
    IMGUI_LIGHT,
  } style = styles::IMGUI_CLASSIC;
  std::string font_path = "";
  float font_size = 0.F;
};

}; // glwnd