// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.vbo.h"
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
    // DO NOTHING
  }

  virtual void final()
  {
    // DO NOTHING
  }

  virtual void on_display()
  {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    {
      glVertex2f(-0.05F, +0.0F);
      glVertex2f(+0.05F, +0.0F);
      glVertex2f(+0.00F, -0.05F);
      glVertex2f(+0.00F, +0.05F);
    }
    glEnd();
    glFlush();
  }
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  // GLWindowExample gl;
  GLWindowExampleImage gl;
  // GLWindowExampleVBO gl;
  // GLWindowExampleSimple gl;
  // GLWindowExampleEvents gl;
  // GLWindowExampleShader gl;
  gl.run();

  return EXIT_SUCCESS;
}