// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.vbo.h"
#include "example.pbo.h"
#include "example.vds.h"
#include "example.text.h"
#include "example.mesh.h"
#include "example.image.h"
#include "example.imgui.h"
#include "example.shader.h"
#include "example.simple.h"
#include "example.events.h"
#include "example.primitive.h"
#include "example.interactive.h"
#include "example.multiview.h"

#include <memory>

int APIENTRY wWinMain(
  _In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPWSTR lpCmdLine,
  _In_ int nShowCmd
)
{
  std::unique_ptr<GLWindow> app(new GLWindow);
  // app->reset(new GLWindowExample);
  // app->reset(new GLWindowExampleSimple);
  // app->reset(new GLWindowExampleEvents);
  // app->reset(new GLWindowExampleShader);
  // app->reset(new GLWindowExampleImage);
  // app->reset(new GLWindowExampleMesh);
  // app->reset(new GLWindowExampleVBO);
  // app->reset(new GLWindowExamplePBO);
  // app->reset(new GLWindowExampleVDS2A);
  // app->reset(new GLWindowExampleVDS4A);
  // app->reset(new GLWindowDearImGUI);
  // app->reset(new GLWindowExampleText2D);
  // app->reset(new GLWindowExamplePrimitive);
  // app->reset(new GLWindowExampleInteractive);
  // app->reset(new GLWindowExampleMultiView);
  app->run();

  return EXIT_SUCCESS;
}