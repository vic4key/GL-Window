#pragma once

/**
 * @file   glwnd.h
 * @author Vic P.
 * @brief  GL Window
 */

#include "defs.h"
#include "base.h"

struct GLFWwindow;

namespace glwnd
{

class GLView;
class GLLayout;
class GLViewPort;
class GLPrimitive;

class GLWindow : public GLBase
{
public:
  GLWindow(const std::string& name = "GL Window", int width = 500, int height = 500, color_t bg = COLOR_GRAY);
  virtual ~GLWindow();

  void run();
  void clear(color_t* pbg = nullptr);

  void set_layout(std::unique_ptr<GLLayout> ptr_layout);
  GLLayout& layout();

  void toggle_fullscreen();

  void enable_fps(bool state = true);
  void enable_debug(bool state = true);
  void enable_coordiates(bool state = true);
  void enable_dear_imgui(bool state = true, dear_imgui_cfg* ptr_dear_imgui_cfg = nullptr);

public:
  GLFWwindow&  window();
  GLViewPort&  viewport();
  GLPrimitive& renderer();

  const std::vector<std::string>& extensions() const;
  const std::vector<std::string>& arb_extensions() const;

private:
  class Impl;
  Impl* m_ptr_impl;
};

}; // glwnd