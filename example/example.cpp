// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.vbo.h"
#include "example.pbo.h"
#include "example.image.h"
#include "example.events.h"
#include "example.simple.h"
#include "example.shader.h"
#include "example.imgui.h"
#include "example.text.h"

#include <memory>

class GLWindowExample : public GLWindow
{
public:
  GLWindowExample() : GLWindow() {};
  virtual ~GLWindowExample() {};

  virtual void initial()
  {
    // your code here
  }

  virtual void final()
  {
    // your code here
  }

  virtual void on_display()
  {
    // your code here
  }
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  std::unique_ptr<GLWindow> gl;
  gl.reset(new GLWindowExample);
  // gl.reset(new GLWindowExampleVBO);
  // gl.reset(new GLWindowExamplePBO);
  // gl.reset(new GLWindowExampleText);
  // gl.reset(new GLWindowExampleImage);
  // gl.reset(new GLWindowExampleSimple);
  // gl.reset(new GLWindowExampleEvents);
  // gl.reset(new GLWindowExampleShader);
  // gl.reset(new GLWindowIMGUI);
  gl->run();

  return EXIT_SUCCESS;
}