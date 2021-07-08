#pragma once

#include <cstdarg>
#include <gl/glew.h>

#include "glwnd/utils.h"

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

/* The bitmap font structure */
typedef struct tagSFG_Font SFG_Font;
struct tagSFG_Font
{
  char* Name;         /* The source font name             */
  int             Quantity;     /* Number of chars in font          */
  int             Height;       /* Height of the characters         */
  const GLubyte** Characters;   /* The characters mapping           */

  float           xorig, yorig; /* Relative origin of the character */
};

/* The stroke font structures */

typedef struct tagSFG_StrokeVertex SFG_StrokeVertex;
struct tagSFG_StrokeVertex
{
  GLfloat         X, Y;
};

typedef struct tagSFG_StrokeStrip SFG_StrokeStrip;
struct tagSFG_StrokeStrip
{
  int             Number;
  const SFG_StrokeVertex* Vertices;
};

typedef struct tagSFG_StrokeChar SFG_StrokeChar;
struct tagSFG_StrokeChar
{
  GLfloat         Right;
  int             Number;
  const SFG_StrokeStrip* Strips;
};

typedef struct tagSFG_StrokeFont SFG_StrokeFont;
struct tagSFG_StrokeFont
{
  char* Name;                       /* The source font name      */
  int             Quantity;                   /* Number of chars in font   */
  GLfloat         Height;                     /* Height of the characters  */
  const SFG_StrokeChar** Characters;          /* The characters mapping    */
};

/*
 * Error Messages.
 */
static void fgError(const char* format, ...)
{
  va_list args;
  va_start(args, format);

  const int KiB = 1024;

  char s[KiB] = { 0 };
  vsprintf_s(s, format, args);

  std::string text = "fgError: ";
  text += s;
  glwnd::utils::log(text);

  va_end(args);
}

static void fgWarning(const char* format, ...)
{
  va_list args;
  va_start(args, format);

  const int KiB = 1024;

  char s[KiB] = { 0 };
  vsprintf_s(s, format, args);

  std::string text = "fgWarning: ";
  text += s;
  glwnd::utils::log(text);

  va_end(args);
}

/* -- PRIVATE FUNCTION DECLARATIONS ---------------------------------------- */

/*
 * A call to this function makes us sure that the Display and Structure
 * subsystems have been properly initialized and are ready to be used
 */
#define  FREEGLUT_EXIT_IF_NOT_INITIALISED( string ) {}

#define  FREEGLUT_INTERNAL_ERROR_EXIT_IF_NOT_INITIALISED( string ) { }

#define  FREEGLUT_INTERNAL_ERROR_EXIT( cond, string, function )  \
  if ( ! ( cond ) )                                              \
  {                                                              \
    fgError ( " ERROR:  Internal error <%s> in function %s",     \
              (string), (function) ) ;                           \
  }

 /*
  * Following definitions are somewhat similar to GLib's,
  * but do not generate any log messages:
  */
#define  freeglut_return_if_fail( expr ) \
    if( !(expr) )                        \
        return;
#define  freeglut_return_val_if_fail( expr, val ) \
    if( !(expr) )                                 \
        return val ;