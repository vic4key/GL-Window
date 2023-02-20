// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.vbo.h"
#include "example.pbo.h"
#include "example.vds.h"
#include "example.text.h"
#include "example.mesh.h"
#include "example.model.h"
#include "example.image.h"
#include "example.imgui.h"
#include "example.shader.h"
#include "example.simple.h"
#include "example.events.h"
#include "example.textglut.h"
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
  GLWindow app;
  app.set_layout(GLLayout::_1x1(app).release());
  //app.layout().replace_view(new GLViewExample, 0);
  //app.layout().replace_view(new GLViewExampleSimple, 0);
  //app.layout().replace_view(new GLViewExampleEvents, 0);
  //app.layout().replace_view(new GLViewExampleShader, 0);
  //app.layout().replace_view(new GLViewExampleImage, 0);
  //app.layout().replace_view(new GLViewExampleMesh, 0);
  //app.layout().replace_view(new GLViewExampleModel, 0);
  //app.layout().replace_view(new GLViewExampleVBO, 0);
  //app.layout().replace_view(new GLViewExamplePBO, 0);
  //app.layout().replace_view(new GLViewExampleVDS2A, 0);
  //app.layout().replace_view(new GLViewExampleVDS4A, 0);
  //app.layout().replace_view(new GLWindowDearImGUI, 0);
  //app.layout().replace_view(new GLViewExampleText2D, 0);
  //app.layout().replace_view(new GLViewExampleTextGLUT, 0);
  //app.layout().replace_view(new GLViewExamplePrimitive, 0);
  //app.layout().replace_view(new GLViewExampleInteractive, 0);
  //app.set_layout(GLLayout::_2x2(app).release());
  //  app.layout().replace_view(new GLViewExampleMultiView, 0);
  //  app.layout().replace_view(new GLViewExampleMultiView, 1);
  //  app.layout().replace_view(new GLViewExampleMultiView, 2);
  //  app.layout().replace_view(new GLViewExampleMultiView, 3);
  app.run();

  return EXIT_SUCCESS;
}