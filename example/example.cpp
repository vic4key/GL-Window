// example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "example.h"

#include <glwnd.h>
#include <utils.h>
#pragma comment(lib, "glwnd.lib")

#include <GL/glew.h>

class GLWindowExample : public GLWindow
{
public:
  GLWindowExample() : GLWindow() {};
  virtual ~GLWindowExample() {};

  virtual void on_display()
  {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    {
      glVertex3f(0.f, 0.5f, 0.f);
      glVertex3f(-0.5f, 0.2f, 0.f);
      glVertex3f(-0.5f, -0.2f, 0.f);
      glVertex3f(0.f, -0.5f, 0.f);
      glVertex3f(0.f, 0.5f, 0.f);
      glVertex3f(0.5f, 0.2f, 0.f);
      glVertex3f(0.5f, -0.2f, 0.f);
      glVertex3f(0.f, -0.5f, 0.f);
    }
    glEnd();
  }

  virtual void on_resize(int width, int height)
  {
    LOG("%d %d", width, height);
  }

  virtual void on_mouse_move(double X, double Y)
  {
    LOG("%.2f %.2f", float(X), float(Y));
  }

  virtual void on_mouse_enter_leave(bool entered, double X, double Y)
  {
    LOG("%s %.2f %.2f", entered ? "enter" : "leave", float(X), float(Y));
  }

  virtual void on_mouse_click(int button, int action, int mods)
  {
    LOG("%d %d %d", button, action, mods);
  }

  virtual void on_mouse_wheel(double delta_x, double delta_y)
  {
    LOG("%.2f %.2f", float(delta_x), float(delta_y));
  }

  virtual void on_keyboard_key(int key, int code, int action, int mods)
  {
    LOG("%d %d %d %d", key, code, action, mods);
  }

  virtual void on_keyboard_char(unsigned int code)
  {
    LOG("%d", code);
  }

  virtual void on_drag_drop(const std::vector<std::string>& paths)
  {
    LOG("%d", paths.size());
    for (auto& path : paths)
    {
      LOG("`%s`", path.c_str());
    }
  }
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  GLWindowExample win;
  win.run();

  return EXIT_SUCCESS;
}