#pragma once

/**
 * @file   view.h
 * @author Vic P.
 * @brief  GL View
 */

#include <gl/glew.h>
#include <glwnd/geometry.h>

#include <glm/glm.hpp>
//#include <glm/core/type.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glwnd
{

class GLViewPort;

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

public:
	void setup(GLViewPort& viewport, int width, int height);
	glm::mat4 get_context_matrix(GLenum type);
	glm::mat4 transform_matrix(const glm::vec3& t, const glm::vec3& r, const glm::vec3& s, glm::mat4* m = nullptr);

private:
	size_t m_index;
	GLViewPort* m_ptr_viewport;
	float l, t, r, b;
	//const p2f& m_left_bottom;
	//const p2f& m_top_right;
};

}; // glwnd