#pragma once

/**
 * @file   glut.cpp
 * @author Vic P.
 * @brief  GL Utility Toolkit Wrapper
 */

#include "glwnd/glut.h"
#include "glwnd/view.h"
#include "glwnd/viewport.h"

#include "gl/freeglut.h"

namespace glwnd
{

namespace glut
{

void render_string(
  GLView* ptr_parent,
  const p2i& position,
  const std::string& text,
  const enum eFontBitmap font)
{
  assert(ptr_parent != nullptr);
  auto p = ptr_parent->viewport().vpc_to_ndc(position);
  render_string(ptr_parent, p, text, font);
}

void render_string(
  GLView* ptr_parent,
  const p2d& position,
  const std::string& text,
  const enum eFontBitmap font)
{
  assert(ptr_parent != nullptr);

  auto pfont = reinterpret_cast<void*>(font);
  auto pstr  = reinterpret_cast<const unsigned char*>(text.c_str());

  glRasterPos2d(position.x(), position.y());
  glutBitmapString(pfont, pstr);
}

void render_string(
  GLView* ptr_parent,
  const p3i& position,
  const std::string& text,
  const enum eFontStroke font,
  const GLdouble scale)
{
  assert(ptr_parent != nullptr);
  auto p = ptr_parent->viewport().vpc_to_ndc(position);
  render_string(ptr_parent, p, text, font, scale);
}

void render_string(
  GLView* ptr_parent,
  const p3d& position,
  const std::string& text,
  const enum eFontStroke font,
  const GLdouble scale)
{
  assert(ptr_parent != nullptr);

  auto pfont = reinterpret_cast<void*>(font);
  auto pstr = reinterpret_cast<const unsigned char*>(text.c_str());

  glPushMatrix();
  {
    glTranslated(position.x(), position.y(), position.z());
    glScaled(scale, scale, scale);
    glutStrokeString(pfont, pstr);
  }
  glPopMatrix();
}

// void calculate_bitmap_string_width(GLView* ptr_parent, const std::string& text, const enum eFontBitmap font, int& result)
// {
//   assert(ptr_parent != nullptr);
// 
//   result = 0;
// 
//   for (auto& e : text)
//   {
//     result += BitmapWidth(reinterpret_cast<void*>(font), e);
//   }
// }
// 
// void calculate_bitmap_string_width(GLView* ptr_parent, const std::string& text, const enum eFontBitmap font, double& result)
// {
//   int w = 0;
//   calculate_bitmap_string_width(ptr_parent, text, font, w);
//   auto p = ptr_parent->viewport().vpc_to_ndc(p2i(w, w));
//   result = std::abs(p.x());
// }

void BitmapString(void* font, const unsigned char* string)
{
  return glutBitmapString(font, string);
}

void BitmapCharacter(void* font, int character)
{
  return glutBitmapCharacter(font, character);
}

int BitmapWidth(void* font, int character)
{
  return glutBitmapWidth(font, character);
}

int BitmapHeight(void* font)
{
  return glutBitmapHeight(font);
}

int BitmapLength(void* font, const unsigned char* string)
{
  return glutBitmapLength(font, string);
}

void StrokeString(void* font, const unsigned char* string)
{
  glutStrokeString(font, string);
}

void StrokeCharacter(void* font, int character)
{
  glutStrokeCharacter(font, character);
}

int StrokeWidth(void* font, int character)
{
  return glutStrokeWidth(font, character);
}

GLfloat StrokeWidthf(void* font, int character)
{
  return glutStrokeWidthf(font, character);
}

GLfloat StrokeHeight(void* font)
{
  return glutStrokeHeight(font);
}

int StrokeLength(void* font, const unsigned char* string)
{
  return glutStrokeLength(font, string);
}

GLfloat StrokeLengthf(void* font, const unsigned char* string)
{
  return glutStrokeLengthf(font, string);
}

}; // glut

}; // glwnd