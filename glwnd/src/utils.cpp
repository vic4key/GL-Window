#pragma once

/**
 * @file   utils.cpp
 * @author Vic P.
 * @brief  Utility
 */

#include "glwnd/utils.h"

#include <Windows.h>

namespace Utils
{

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

}; // Utils