// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.simple.h"
#include "example.events.h"
#include "example.shader.h"

class GLWindowExample : public GLWindow
{
public:
  GLWindowExample() : GLWindow() {};
  virtual ~GLWindowExample() {};

  virtual void initial()
  {
    // DO NOTHING
  }

  virtual void final()
  {
    // DO NOTHING
  }

  virtual void on_display()
  {
    // DO NOTHING
  }
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  GLWindowExample gl;
  // GLWindowExampleSimple gl;
  // GLWindowExampleEvents gl;
  // GLWindowExampleShader gl;
  gl.run();

  return EXIT_SUCCESS;
}