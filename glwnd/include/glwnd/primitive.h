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

class GLPrimitive
{
public:
	GLPrimitive(GLWindow& parent);
	virtual ~GLPrimitive();

	void circle(const p2d& center, double radius, bool fill = false, int nsegments = 100);
	void circle(const p2i& center, int radius, bool fill = false, int nsegments = 100);

	void line(const p2d& p1, const p2d& p2);
	void line(const p2i& p1, const p2i& p2);

private:
	GLWindow& m_parent;
};

}; // glwnd