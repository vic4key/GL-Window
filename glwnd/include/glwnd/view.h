#pragma once

/**
 * @file   view.h
 * @author Vic P.
 * @brief  GL View
 */

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "geometry.h"
#include "viewport.h"

namespace glwnd
{

class GLView
{
public:
	GLView(const p2f& lb, const p2f& tr, const size_t index);
	virtual ~GLView();

	GLView(const GLView& right);
	GLView& operator=(const GLView& right);

public:
	void display();
	size_t index() const;
	GLViewPort& viewport();

public:
	void setup(GLViewPort& viewport, int width, int height);

	glm::mat4 get_context_matrix(GLenum type);
	void set_context_matrix(GLenum mode, const glm::mat4& matrix);
	glm::mat4 transform_context_matrix(GLenum type, const glm::vec3& t, const glm::vec3& r, const glm::vec3& s);

	glm::mat4 transform_matrix(const glm::vec3& t, const glm::vec3& r, const glm::vec3& s, glm::mat4* m = nullptr);

private:
	GLViewPort m_viewport;
	size_t m_index;
	p2f m_lt;
	p2f m_rb;
};

}; // glwnd