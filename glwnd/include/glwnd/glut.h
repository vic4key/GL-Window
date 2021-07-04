#pragma once

/**
 * @file   glut.h
 * @author Vic P.
 * @brief  GL Utility Toolkit Wrapper
 */

#include <string>

#include <gl/glew.h>

#include "geometry.h"

namespace glwnd
{

class GLView;

namespace glut
{

enum class bitmap_fonts
{
	GLUT_BITMAP_9_BY_15        = 0x0002,
	GLUT_BITMAP_8_BY_13        = 0x0003,
	GLUT_BITMAP_TIMES_ROMAN_10 = 0x0004,
	GLUT_BITMAP_TIMES_ROMAN_24 = 0x0005,
	GLUT_BITMAP_HELVETICA_10   = 0x0006,
	GLUT_BITMAP_HELVETICA_12   = 0x0007,
	GLUT_BITMAP_HELVETICA_18   = 0x0008,
};

enum class stroke_fonts
{
  GLUT_STROKE_ROMAN = 0x0000,
  GLUT_STROKE_MONO_ROMAN = 0x0001,
};

void render_string(
	GLView* ptr_parent,
	const p2i& position,
	const std::string& text,
	const enum bitmap_fonts font = bitmap_fonts::GLUT_BITMAP_9_BY_15);

void render_string(
	GLView* ptr_parent,
	const p2d& position,
	const std::string& text,
  const enum bitmap_fonts font = bitmap_fonts::GLUT_BITMAP_9_BY_15);

void render_string(
  GLView* ptr_parent,
  const p3i& position,
  const std::string& text,
  const enum stroke_fonts font = stroke_fonts::GLUT_STROKE_ROMAN,
	const GLdouble scale = 0.0005);

void render_string(
  GLView* ptr_parent,
  const p3d& position,
  const std::string& text,
  const enum stroke_fonts font = stroke_fonts::GLUT_STROKE_ROMAN,
  const GLdouble scale = 0.0005);

// void calculate_bitmap_string_width(
// 	GLView* ptr_parent,
// 	const std::string& text,
// 	const enum eFontBitmap font, int& result);
// 
// void calculate_bitmap_string_width(
// 	GLView* ptr_parent,
// 	const std::string& text,
// 	const enum eFontBitmap font, double& result);

void    BitmapString(void* font, const unsigned char* string);
void    BitmapCharacter(void* font, int character);
int     BitmapWidth(void* font, int character);
int     BitmapHeight(void* font);
int     BitmapLength(void* font, const unsigned char* string);

void    StrokeString(void* font, const unsigned char* string);
void    StrokeCharacter(void* font, int character);
int     StrokeWidth(void* font, int character);
GLfloat StrokeWidthf(void* font, int character); /* GLUT 3.8 */
GLfloat StrokeHeight(void* font);
int     StrokeLength(void* font, const unsigned char* string);
GLfloat StrokeLengthf(void* font, const unsigned char* string); /* GLUT 3.8 */

}; // glut

}; // glwnd