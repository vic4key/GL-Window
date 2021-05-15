#pragma once

/**
 * @file   debug.inl
 * @author Vic P.
 * @brief  OpenGL Debugging Error
 */

#include <GL/glew.h>
#include <Windows.h>
#include <sstream>

#define CASE(code) case code: ss << #code ; break

#define glCheckError() glwndCheckError(__FILE__, __LINE__)

static GLenum glwndCheckError(const char* file, int line)
{
  std::stringstream ss;

  GLenum error = GL_NO_ERROR;
  while (error = glGetError())
  {
    switch (error)
    {
      CASE(GL_NO_ERROR);
      CASE(GL_INVALID_ENUM);
      CASE(GL_INVALID_VALUE);
      CASE(GL_INVALID_OPERATION);
      CASE(GL_STACK_OVERFLOW);
      CASE(GL_STACK_UNDERFLOW);
      CASE(GL_OUT_OF_MEMORY);
      CASE(GL_INVALID_FRAMEBUFFER_OPERATION);
    }

    ss << error << " | " << file << " (" << line << ")" << std::endl;
  }

  int response = MessageBoxA(GetActiveWindow(), ss.str().c_str(), "ERROR", MB_OKCANCEL | MB_ICONERROR);
  if (response == IDCANCEL)
  {
    TerminateProcess(GetCurrentProcess(), 0);
  }

  return error;
}

static void APIENTRY glDebugOutput(
  GLenum source,
  GLenum type,
  unsigned int id,
  GLenum severity,
  GLsizei length,
  const char* message,
  const void* userParam)
{
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
  {
    return; // ignore these non-significant error codes
  }

  std::stringstream ss;

  ss << "ID: " << id << std::endl;

  ss << std::endl;

  ss << "Description: " << message << std::endl;

  ss << "Source: ";
  switch (source)
  {
    CASE(GL_DEBUG_SOURCE_API);
    CASE(GL_DEBUG_SOURCE_WINDOW_SYSTEM);
    CASE(GL_DEBUG_SOURCE_SHADER_COMPILER);
    CASE(GL_DEBUG_SOURCE_THIRD_PARTY);
    CASE(GL_DEBUG_SOURCE_APPLICATION);
    CASE(GL_DEBUG_SOURCE_OTHER);
  }
  ss << std::endl;

  ss << std::endl;

  ss << "Type: ";
  switch (type)
  {
    CASE(GL_DEBUG_TYPE_ERROR);
    CASE(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR);
    CASE(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR);
    CASE(GL_DEBUG_TYPE_PORTABILITY);
    CASE(GL_DEBUG_TYPE_PERFORMANCE);
    CASE(GL_DEBUG_TYPE_MARKER);
    CASE(GL_DEBUG_TYPE_PUSH_GROUP);
    CASE(GL_DEBUG_TYPE_POP_GROUP);
    CASE(GL_DEBUG_TYPE_OTHER);
  }
  ss << std::endl;

  ss << std::endl;

  ss << "Severity: ";
  switch (severity)
  {
    CASE(GL_DEBUG_SEVERITY_HIGH);
    CASE(GL_DEBUG_SEVERITY_MEDIUM);
    CASE(GL_DEBUG_SEVERITY_LOW);
    CASE(GL_DEBUG_SEVERITY_NOTIFICATION);
  }
  ss << std::endl;

  int response = MessageBoxA(GetActiveWindow(), ss.str().c_str(), "DEBUG", MB_OKCANCEL | MB_ICONERROR);
  if (response == IDCANCEL)
  {
    TerminateProcess(GetCurrentProcess(), 0);
  }
}
