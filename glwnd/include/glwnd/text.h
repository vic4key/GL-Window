#pragma once

/**
 * @file   text.h
 * @author Vic P.
 * @brief  Text Render
 */

#include <GL/glew.h>
#include <string>

#include "types.h"

class  GLWindow;
struct GLTtext;

class TextRender
{
public:
	enum class eTextAlignment
	{
    ALIGN_TOP,
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_BOTTOM,
    ALIGN_CENTER,
	};

	TextRender();
	virtual ~TextRender();

	bool setup(GLWindow* ptr_parent);

	void draw(
		const std::string& text,
		float x,
		float y,
		glwnd::glcolor_t<float> color,
		eTextAlignment ha = eTextAlignment::ALIGN_LEFT,
		eTextAlignment va = eTextAlignment::ALIGN_TOP,
		float scale = 1.F
	);

private:
	GLWindow* m_ptr_parent;
	GLTtext*  m_ptr_text;
};