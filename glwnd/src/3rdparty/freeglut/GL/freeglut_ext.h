#pragma once

#include <gl/glew.h>

#include "freeglut_defs.h"

/*
 * Font stuff, see fg_font.c
 */
FGAPI int     FGAPIENTRY glutBitmapHeight( void* font );
FGAPI void    FGAPIENTRY glutBitmapString( void* font, const unsigned char *string );
FGAPI GLfloat FGAPIENTRY glutStrokeHeight( void* font );
FGAPI void    FGAPIENTRY glutStrokeString( void* font, const unsigned char *string );
