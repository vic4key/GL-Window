#pragma once

/**
 * @file   layout.h
 * @author Vic P.
 * @brief  GL Layout
 */

#include <vector>
#include <memory>

#include "geometry.h"

namespace glwnd
{

class GLView;
class GLWindow;

class GLLayout
{
public:
	GLLayout(GLWindow& parent);
	virtual ~GLLayout();

	GLLayout(const GLLayout& right);
	GLLayout& operator=(const GLLayout& right);

	std::vector<GLView*>& views();

	void add_view(const p2f& left_bottom, const p2f& top_left);
	GLView* get_active_view_from_mouse_position(const p2i& point);

  static std::unique_ptr<GLLayout> _empty(GLWindow& parent);
  static std::unique_ptr<GLLayout> _1x1(GLWindow& parent);
  static std::unique_ptr<GLLayout> _1x2(GLWindow& parent);
  static std::unique_ptr<GLLayout> _2x1(GLWindow& parent);
  static std::unique_ptr<GLLayout> _2x2(GLWindow& parent);

private:
	void remove_all_views();

private:
	GLWindow* m_ptr_parent;
	std::vector<GLView*> m_ptr_views;
};

}; // glwnd