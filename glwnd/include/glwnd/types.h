#pragma once

/**
 * @file   types.h
 * @author Vic P.
 * @brief  Data Types
 */

namespace glwnd
{

typedef unsigned char  byte_t;
typedef unsigned short word_t;
typedef unsigned int   dword_t;

union color_t
{
  dword_t rgba;
  struct
  {
    byte_t r, g, b, a;
  };

  color_t(dword_t _rgba) : rgba(_rgba) {};
  color_t(byte_t _r, byte_t _g, byte_t _b, byte_t _a = 0) : r(_r), g(_g), b(_b), a(_a) {};

  color_t& operator=(dword_t _rgba)
  {
    rgba = _rgba;
  }

  color_t& operator=(const color_t& _rgba)
  {
    rgba = _rgba.rgba;
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

  glcolor_t& operator=(const glcolor_t& _rgba)
  {
    r = _rgba.r;
    g = _rgba.g;
    b = _rgba.b;
    a = _rgba.a;
  }
};

}; // glwnd