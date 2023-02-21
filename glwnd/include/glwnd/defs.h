#pragma once

/**
 * @file   defs.h
 * @author Vic P.
 * @brief  Definitions
 */

#include <gl/glew.h>
#include <memory>

#include "types.h"

namespace glwnd
{

const color_t COLOR_BLACK = 0xFF000000;
const color_t COLOR_WHITE = 0xFFFFFFFF;
const color_t COLOR_GRAY  = 0xFF303030;

static GLuint GL_INVALID_ID = -1;

}; // glwnd

#define glwnd_max(a,b) (((a) > (b)) ? (a) : (b))
#define glwnd_min(a,b) (((a) < (b)) ? (a) : (b))

#define glwnd_3rd_stringize_ex(s) #s
#define glwnd_3rd_stringize(s) glwnd_3rd_stringize_ex(s)
#define glwnd_3rd_include(s)   glwnd_3rd_stringize(../3rdparty/s)

#define GLWND_DELETE_UNUSED_OPERATORS(T)\
  T& operator=(T&&) = delete;\
  T& operator=(const T&) = delete;\
  bool operator==(const T&) = delete;\
  bool operator!=(const T&) = delete;\
  bool operator< (const T&) = delete;\
  bool operator> (const T&) = delete;\
  bool operator<=(const T&) = delete;\
  bool operator>=(const T&) = delete;\
  // auto operator<=>(const T&) const = delete;

template<class Container>
inline int size_of(const Container& container)
{
  return int(container.size()) * sizeof(Container::value_type);
}
