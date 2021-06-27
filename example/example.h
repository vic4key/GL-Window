#pragma once

#include "resource.h"

#include <gl/glew.h>
#include <glwnd/glwnd>
#include <glwnd/view.h>
using namespace glwnd;

class GLViewExample : public GLView
{
public:
  GLViewExample() : GLView() {}
  virtual ~GLViewExample() {}

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