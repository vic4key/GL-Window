#pragma once

/**
 * @file   utils.cpp
 * @author Vic P.
 * @brief  Utility
 */

#include "glwnd/utils.h"

#include <Windows.h>
#include <fstream>
#include <sstream>

namespace glwnd
{

namespace utils
{

void load_file(const std::string& file_path, std::vector<unsigned char>& data)
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

std::string load_text_file(const std::string& file_path)
{
  std::ifstream f(file_path);
  std::stringstream ss;
  ss << f.rdbuf();
  return ss.str();
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

void image_channel_to_format_types(int channel, GLint& iformat, GLint& format)
{
  switch (channel)
  {
  case 1: // gray
    format  = GL_LUMINANCE;
    iformat = GL_LUMINANCE8;
    break;

  case 3: // rgb
    format  = GL_RGB;
    iformat = GL_RGB8;
    break;

  case 4: // rgba
    format  = GL_RGBA;
    iformat = GL_RGBA8;
    break;

  default:
    break;
  }
}

bool is_point_inside_rect(const p2i& point, const r4i& rect)
{
  bool result = \
    point.x() >= rect.left() &&
    point.x() <= rect.right() &&
    point.y() >= rect.bottom() &&
    point.y() <= rect.top();
  return result;
}

int msg(const char* text, const char* title, int type)
{
  std::string s;

  if (title == nullptr)
  {
    char file_path[MAX_PATH] = { 0 };
    GetModuleFileNameA(nullptr, file_path, sizeof(file_path));
    s = file_path;
    s = s.substr(s.find_last_of("/\\") + 1);
  }
  else
  {
    s = title;
  }

  return MessageBoxA(GetActiveWindow(), text, s.c_str(), type);
}

int msg_info(const char* text, const char* title)
{
  return msg(text, title, MB_OK | MB_ICONINFORMATION);
}

int msg_warn(const char* text, const char* title)
{
  return msg(text, title, MB_OK | MB_ICONWARNING);
}

int msg_error(const char* text, const char* title)
{
  return msg(text, title, MB_OK | MB_ICONERROR);
}

}; // utils

}; // glwnd