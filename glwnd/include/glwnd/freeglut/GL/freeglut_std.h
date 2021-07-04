#pragma once

#define FGAPI
#define FGAPIENTRY

/*
 * GLUT API macro definitions -- fonts definitions
 *
 * Steve Baker suggested to make it binary compatible with GLUT:
 */

#define  GLUT_STROKE_ROMAN               ((void *)0x0000)
#define  GLUT_STROKE_MONO_ROMAN          ((void *)0x0001)
#define  GLUT_BITMAP_9_BY_15             ((void *)0x0002)
#define  GLUT_BITMAP_8_BY_13             ((void *)0x0003)
#define  GLUT_BITMAP_TIMES_ROMAN_10      ((void *)0x0004)
#define  GLUT_BITMAP_TIMES_ROMAN_24      ((void *)0x0005)
#define  GLUT_BITMAP_HELVETICA_10        ((void *)0x0006)
#define  GLUT_BITMAP_HELVETICA_12        ((void *)0x0007)
#define  GLUT_BITMAP_HELVETICA_18        ((void *)0x0008)

/*
 * Font stuff, see fg_font.c
 */
FGAPI void    FGAPIENTRY glutBitmapCharacter(void* font, int character);
FGAPI int     FGAPIENTRY glutBitmapWidth(void* font, int character);