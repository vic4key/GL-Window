#pragma once

/**
 * @file   defs.h
 * @author Vic P.
 * @brief  Definitions
 */

#include <GL/glew.h>

#include "types.h"

#define glwnd_3rd_stringize_ex(s) #s
#define glwnd_3rd_stringize(s) glwnd_3rd_stringize_ex(s)
#define glwnd_3rd_include(s)   glwnd_3rd_stringize(../3rdparty/s)

namespace glwnd
{

const color_t COLOR_BLACK = 0xFF000000;
const color_t COLOR_WHITE = 0xFFFFFFFF;
const color_t COLOR_GRAY  = 0xFF303030;

static GLuint GL_INVALID_ID = -1;

}; // glwnd