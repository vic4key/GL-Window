#pragma once

/**
 * @file   utils.h
 * @author Vic P.
 * @brief  Utility
 */

#include <gl/glew.h>
#include <string>
#include <vector>

#include "types.h"

namespace glwnd
{

namespace utils
{

template <class std_string_t>
std::vector<std_string_t> split_string_t(const std_string_t& str, const std_string_t& sep)
{
  std::vector<std_string_t> l;
  l.clear();

  if (str.empty())
  {
    return l;
  }

  bool to_remove_empty = true;

  std_string_t s(str), sub;

  size_t start = 0;
  size_t end = s.find(sep);
  while (end != std_string_t::npos)
  {
    sub = s.substr(start, end - start);
    if (!sub.empty() || !to_remove_empty) l.push_back(std_string_t(sub.c_str()));
    start = end + sep.length();
    end = s.find(sep, start);
  }

  sub = s.substr(start, end);
  if (!sub.empty() || !to_remove_empty) l.push_back(std_string_t(sub.c_str()));

  return l;
}

template <typename T>
T conv_range(T l1, T h1, T l2, T h2, T v)
{
  return T(l2 + double(v - l1) * double(h2 - l2) / double(h1 - l1));
}

template <typename T>
T align_up(T v, T a = T(4)) // default alignent = 4
{
  return ((v + (a - 1)) & ~(a - 1));
}

void load_file(const std::string& file_path, std::vector<unsigned char>& data);

std::string load_text_file(const std::string& file_path);

std::string log(const std::string format, ...);

GLuint gl_sizeof_type(GLenum type);

void image_channel_to_format_types(int channel, GLint& iformat, GLint& format);

}; // utils

}; // glwnd

#define LOG(...) utils::log(__FUNCTION__ " " __VA_ARGS__)