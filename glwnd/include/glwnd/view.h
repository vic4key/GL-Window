#pragma once

/**
 * @file   view.h
 * @author Vic P.
 * @brief  GL View
 */

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "event.h"
#include "geometry.h"
#include "viewport.h"
#include "primitive.h"

namespace glwnd
{

class FPS;

class GLView : public GLEvent, public GLPrimitive
{
	friend GLWindow;

public:
	GLView();
	GLView(const p2f& lb, const p2f& tr);
	virtual ~GLView();

	GLView(const GLView& right);
	GLView& operator=(const GLView& right);

public:
	void set_parent(GLWindow& parent);
	void set_index(const size_t index);
	size_t index() const;

	GLWindow& parent();
	GLViewPort& viewport();

	void setup(GLViewPort& viewport, int width, int height);

	glm::mat4 transform_matrix(const glm::vec3& t, const glm::vec3& r, const glm::vec3& s, glm::mat4* m = nullptr);

	glm::mat4 transform_context_matrix(GLenum type, const glm::vec3& t, const glm::vec3& r, const glm::vec3& s);
	void set_context_matrix(GLenum mode, const glm::mat4& matrix);
	glm::mat4 get_context_matrix(GLenum type);

protected:
  void display_fps();
  void enable_fps(bool state = true);
  void enable_coordiates(bool state = true);

protected:
	GLWindow*  m_ptr_parent;
	GLViewPort m_viewport;
	size_t m_index;
	p2f m_lt, m_rb;
	FPS* m_ptr_fps;

  bool m_fps_enabled;
  bool m_coordiates_enabled;
};

class GLViewDefault : public GLView
{
public:
	GLViewDefault() : GLView() {}
	GLViewDefault(const p2f& lb, const p2f& tr) : GLView(lb, tr) {}
	virtual void on_display() {}
};

}; // glwnd