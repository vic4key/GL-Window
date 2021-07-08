#pragma once

#include <gl/glew.h>

#include "freeglut_defs.h"

/*
 * Font stuff, see fg_font.c
 */
FGAPI void    FGAPIENTRY glutBitmapCharacter( void* font, int character );
FGAPI int     FGAPIENTRY glutBitmapWidth( void* font, int character );
FGAPI int     FGAPIENTRY glutBitmapLength( void* font, const unsigned char* string );
FGAPI void    FGAPIENTRY glutStrokeCharacter( void* font, int character );
FGAPI int     FGAPIENTRY glutStrokeWidth( void* font, int character );
FGAPI GLfloat FGAPIENTRY glutStrokeWidthf( void* font, int character ); /* GLUT 3.8 */
FGAPI int     FGAPIENTRY glutStrokeLength( void* font, const unsigned char* string );
FGAPI GLfloat FGAPIENTRY glutStrokeLengthf( void* font, const unsigned char *string ); /* GLUT 3.8 */
