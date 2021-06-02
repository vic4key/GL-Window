#pragma once

/**
 * @file   tex2d.h
 * @author Vic P.
 * @brief  Texture 2D
 */

#include <GL/glew.h>

#include <string>

namespace glwnd
{

// required glEnable(GL_TEXTURE_2D)

class Tex2D
{
public:
	Tex2D(GLint wrap = GL_CLAMP, GLint filter = GL_LINEAR);
	virtual ~Tex2D();

	bool initialize_from_image_file(const std::string& file_path);
	bool initialize(GLsizei width, GLsizei height, GLvoid* ptr_pixels, GLint iformat, GLenum format);

	void use(bool state = true);

private:
	GLuint m_id;
	GLint  m_wrap;
	GLint  m_filter;
	bool   m_initialized;
};

}; // glwnd