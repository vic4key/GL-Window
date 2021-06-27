#pragma once

#include "example.h"

#include glwnd_3rd_include(imgui-1.82/imgui.h)

class GLWindowDearImGUI : public GLView
{
public:
  GLWindowDearImGUI() : GLView() {}
  virtual ~GLWindowDearImGUI() {}

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