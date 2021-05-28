#pragma once

/**
 * @file   primitive.h
 * @author Vic P.
 * @brief  Rendering Primitives
 */

#include "geometry.h"

#include <gl/glew.h>

#include <initializer_list>

namespace glwnd
{

class GLWindow;
class GLViewPort;

class TextRender2D;

class GLPrimitive
{
public:
	GLPrimitive();
	virtual ~GLPrimitive();

	void initialize(GLWindow* ptr_parent);

  enum class circle_t : int
  {
    stipple = GL_LINES, // alias for stipple
    solid = GL_LINE_LOOP,
    fill = GL_POLYGON,
  };

	void circle(const p2d& center, double radius, circle_t type = circle_t::solid, int nsegments = 100);
	void circle(const p2i& center, int radius, circle_t type = circle_t::solid, int nsegments = 100);

  enum class line_t : int
  {
    stipple, // alias for tipple
    solid,
  };

	void line(const p2d& p1, const p2d& p2, line_t type = line_t::solid, int nsegments = 10);
	void line(const p2i& p1, const p2i& p2, line_t type = line_t::solid, int nsegments = 10);

  void scatter(const std::initializer_list<p2d>& points);
  void scatter(const std::initializer_list<p2i>& points);

	TextRender2D& text();

private:
	GLWindow* m_ptr_parent;
	TextRender2D* m_ptr_text_render; // default text renderer 2D
};

}; // glwnd