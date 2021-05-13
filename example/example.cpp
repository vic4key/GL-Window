// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.vbo.h"
#include "example.pbo.h"
#include "example.image.h"
#include "example.events.h"
#include "example.simple.h"
#include "example.shader.h"

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
  GLWindowExample gl;
  // GLWindowExampleVBO gl;
  // GLWindowExamplePBO gl;
  // GLWindowExampleImage gl;
  // GLWindowExampleSimple gl;
  // GLWindowExampleEvents gl;
  // GLWindowExampleShader gl;
  gl.run();

  return EXIT_SUCCESS;
}