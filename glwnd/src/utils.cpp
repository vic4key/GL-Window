#pragma once

/**
 * @file   utils.cpp
 * @author Vic P.
 * @brief  Utility
 */

#include "glwnd/utils.h"

#include <Windows.h>

namespace glwnd
{

namespace utils
{

void read_file(const std::string& file_path, std::vector<unsigned char>& data)
{
	FILE* f = nullptr;
	fopen_s(&f, file_path.c_str(), "rb");

	fseek(f, 0, SEEK_END);
	size_t file_size = ftell(f);

	data.resize(file_size);
	fseek(f, 0, SEEK_SET);
	fread(&data[0], 1, file_size, f);

	fclose(f);
}

std::string log(const std::string format, ...)
{
  va_list args;
  va_start(args, format);

  const int KiB = 1024;

  char s[KiB] = { 0 };
  vsprintf_s(s, format.c_str(), args);

  va_end(args);

  OutputDebugStringA(s);

  return s;
}

GLuint gl_sizeof_type(GLenum type)
{
  GLuint result = 0;

  switch (type)
  {
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:
    result = 1;
    break;

  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
  case GL_2_BYTES:
    result = 2;
    break;

  case GL_INT:
  case GL_UNSIGNED_INT:
  case GL_FLOAT:
  case GL_4_BYTES:
    result = 4;
    break;

  case GL_3_BYTES:
    result = 3;
    break;

  case GL_DOUBLE:
    result = 8;
    break;

  default:
    break;
  }

  return result;
}

}; // utils

}; // glwnd