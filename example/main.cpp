// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.vbo.h"
#include "example.pbo.h"
#include "example.vds.h"
#include "example.text.h"
#include "example.image.h"
#include "example.imgui.h"
#include "example.shader.h"
#include "example.sample.h"
#include "example.simple.h"
#include "example.events.h"
#include "example.primitive.h"

#include <memory>

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  std::unique_ptr<GLWindow> gl;
  gl.reset(new GLWindowExampleSample);
  // gl.reset(new GLWindowExampleSimple);
  // gl.reset(new GLWindowExampleEvents);
  // gl.reset(new GLWindowExampleShader);
  // gl.reset(new GLWindowExampleImage);
  // gl.reset(new GLWindowExampleVBO);
  // gl.reset(new GLWindowExamplePBO);
  // gl.reset(new GLWindowExampleVDS2A);
  // gl.reset(new GLWindowExampleVDS4A);
  // gl.reset(new GLWindowIMGUI);
  // gl.reset(new GLWindowExampleText2D);
  // gl.reset(new GLWindowExamplePrimitive);
  gl->run();

  return EXIT_SUCCESS;
}