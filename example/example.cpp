// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.simple.h"
#include "example.events.h"
#include "example.shader.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  GLWindowExampleSimple gl;
  // GLWindowExampleEvents gl;
  // GLWindowExampleShader gl;
  gl.run();

  return EXIT_SUCCESS;
}