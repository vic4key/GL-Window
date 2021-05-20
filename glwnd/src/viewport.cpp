/**
 * @file   viewport.cpp
 * @author Vic P.
 * @brief  GL ViewPort
 */

#include "glwnd/viewport.h"
#include "glwnd/glwnd.h"

namespace glwnd
{

GLViewPort::GLViewPort(GLWindow* ptr_parent) : m_ptr_parent(ptr_parent)
{
}

GLViewPort::~GLViewPort()
{
}

GLViewPort::coordinate_t& GLViewPort::coordinate()
{
  return m_coordinate;
}

}; // glwnd