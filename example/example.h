#pragma once

#include "resource.h"

#include <gl/glew.h>
#include <glwnd/glwnd>
using namespace glwnd;

class GLWindowExample : public GLWindow
{
public:
  GLWindowExample() : GLWindow() {}
  virtual ~GLWindowExample() {}

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

private:
  // your data here
};