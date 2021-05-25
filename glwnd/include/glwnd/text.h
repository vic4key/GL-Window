#pragma once

/**
 * @file   text.h
 * @author Vic P.
 * @brief  Text Render 2D
 */

#include <GL/glew.h>
#include <string>
#include <map>

#include "geometry.h"

struct GLTtext;

namespace glfreetype
{
	struct font_data;
};

namespace glwnd
{

class  GLWindow;

static const int   INVALID_FONT_ID = -1;
static const int   DEFAULT_FONT_SIZE = 14;
static const char* DEFAULT_FONT_NAME = "C:\\Windows\\Fonts\\georgia.ttf"; // georgia.ttf cour.ttf

class TextRender2D
{
public:
	TextRender2D();
	virtual ~TextRender2D();

	bool initialize(GLWindow* ptr_parent, const std::string& name = DEFAULT_FONT_NAME, int size = DEFAULT_FONT_SIZE);
	int  add_font(const std::string& name, const int size);
	void render_text(const std::string& text, const p2i& position, int* ptr_font_id = nullptr);
	void render_text(const std::string& text, const p2d& position, int* ptr_font_id = nullptr);
	size_t get_num_added_fonts();

private:
	GLWindow* m_ptr_parent;
	int m_current_font_id;
	std::map<int, glfreetype::font_data*> m_fonts;
};

}; // glwnd