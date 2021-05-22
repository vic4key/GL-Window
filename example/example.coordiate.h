#pragma once

#include "example.h"

class GLWindowExampleCoordiate : public GLWindow
{
public:
  GLWindowExampleCoordiate() : GLWindow() {}
  virtual ~GLWindowExampleCoordiate() {}

  virtual void initial()
  {
    this->enable_coordiates();
  }
};