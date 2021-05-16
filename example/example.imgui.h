#pragma once

#include "example.h"

#include glwnd_3rd_include(imgui-1.82/imgui.h)

class GLWindowIMGUI : public GLWindow
{
public:
  GLWindowIMGUI() : GLWindow()
  {
    imgui_cfg cfg;
    cfg.style = imgui_cfg::styles::IMGUI_CLASSIC;
    cfg.font_path = "C:\\Windows\\Fonts\\georgia.ttf";
    cfg.font_size = 16.F;
    this->enable_imgui(true, &cfg);
  }

  virtual ~GLWindowIMGUI() {};

  virtual void on_display()
  {
    ImGui::Begin("Dear ImGui");
    {
      ImGui::Text("Halo, Dear ImGui inside a GL Window.");
    }
    ImGui::End();

    static bool demo_window = true;
    if (demo_window)
    {
      ImGui::ShowDemoWindow(&demo_window);
    }
  }
};