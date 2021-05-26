#pragma once

/**
 * @file   primitive.h
 * @author Vic P.
 * @brief  Rendering Primitives
 */

#include "geometry.h"

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

	void circle(const p2d& center, double radius, bool fill = false, int nsegments = 100);
	void circle(const p2i& center, int radius, bool fill = false, int nsegments = 100);

	void line(const p2d& p1, const p2d& p2);
	void line(const p2i& p1, const p2i& p2);

	TextRender2D& text();

private:
	GLWindow* m_ptr_parent;
	TextRender2D* m_ptr_text_render; // default text renderer 2D
};

}; // glwnd