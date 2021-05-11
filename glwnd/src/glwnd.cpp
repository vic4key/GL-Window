/**
 * @file   glwnd.cpp
 * @author Vic P.
 * @brief  GL Window
 */

#include "glwnd/glwnd.h"
#include "glwnd/utils.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include <Windows.h>
#include <cassert>

/**
 * CGLWindow - Implementation
 */

class GLWindow::Impl
{
  friend GLWindow;

public:
  Impl(GLWindow* ptr_parent, const std::string& name, int width, int height, COLORREF bg = RGB(0, 0, 0));
  virtual ~Impl();

  void on_display();
  void on_resize(int Width, int Height);

  void on_mouse_move(double x, double y);
  void on_mouse_enter_leave(bool entered, double x, double y);
  void on_mouse_click(int button, int action, int mods);
  void on_mouse_wheel(double delta_x, double delta_y);

  void on_keyboard_key(int key, int code, int action, int mods);
  void on_keyboard_char(unsigned int code);

  void on_drag_drop(const std::vector<std::string>& paths);

  int run();

private:
  static void error(int code, const char* description);
  static void resize(GLFWwindow* ptr_window, int width, int height);

  static void mouse_move(GLFWwindow* ptr_window, double x, double y);
  static void mouse_enter_leave(GLFWwindow* ptr_window, int entered);
  static void mouse_click(GLFWwindow* ptr_window, int button, int action, int mods);
  static void mouse_wheel(GLFWwindow* ptr_window, double delta_x, double delta_y);

  static void keyboard_key(GLFWwindow* ptr_window, int key, int code, int action, int mods);
  static void keyboard_char(GLFWwindow* ptr_window, unsigned int code);

  static void drag_drop(GLFWwindow* ptr_window, int cout, const char** pptr_paths);

  static void project(int width, int height);

  int create();
  int destroy();

private:
  GLWindow*   m_ptr_parent;
  GLFWwindow* m_ptr_window;

  std::string m_name;
  int m_width;
  int m_height;
  COLORREF m_bg;

  std::vector<std::string> m_extensions;
  std::vector<std::string> m_arb_extensions;
};

GLWindow::Impl::Impl(GLWindow* ptr_parent, const std::string& name, int width, int height, COLORREF bg)
  : m_ptr_window(nullptr), m_ptr_parent(ptr_parent)
  , m_name(name), m_width(width), m_height(height), m_bg(bg)
{
}

GLWindow::Impl::~Impl()
{
}

void GLWindow::Impl::on_display()
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  auto r = GetRValue(m_bg) / 255.F;
  auto g = GetGValue(m_bg) / 255.F;
  auto b = GetBValue(m_bg) / 255.F;

  glClearColor(r, g, b, 1.F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  {
    m_ptr_parent->on_display();
  }
  glPopAttrib();
  glPopMatrix();

  glFlush();
}

void GLWindow::Impl::on_resize(int width, int height)
{
  m_ptr_parent->on_resize(width, height);
}

void GLWindow::Impl::on_mouse_move(double x, double y)
{
  m_ptr_parent->on_mouse_move(x, y);
}

void GLWindow::Impl::on_mouse_enter_leave(bool entered, double x, double y)
{
  m_ptr_parent->on_mouse_enter_leave(entered, x, y);
}

void GLWindow::Impl::on_mouse_click(int button, int action, int mods)
{
  m_ptr_parent->on_mouse_click(button, action, mods);
}

void GLWindow::Impl::on_mouse_wheel(double delta_x, double delta_y)
{
  m_ptr_parent->on_mouse_wheel(delta_x, delta_y);
}

void GLWindow::Impl::on_keyboard_key(int key, int code, int action, int mods)
{
  m_ptr_parent->on_keyboard_key(key, code, action, mods);
}

void GLWindow::Impl::on_keyboard_char(unsigned int code)
{
  m_ptr_parent->on_keyboard_char(code);
}

void GLWindow::Impl::on_drag_drop(const std::vector<std::string>& paths)
{
  m_ptr_parent->on_drag_drop(paths);
}

void GLWindow::Impl::error(int code, const char* description)
{
  Utils::log("GLFW -> %d, %s", code, description);
}

void GLWindow::Impl::resize(GLFWwindow* ptr_window, int width, int height)
{
  project(width, height);

  auto ptr_parent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent != nullptr);

  ptr_parent->on_resize(width, height);

  ptr_parent->on_display();

  glfwPollEvents(); //  TODO: Vic. Recheck.
  glfwSwapBuffers(ptr_window);
}

void GLWindow::Impl::mouse_move(GLFWwindow* ptr_window, double x, double y)
{
  auto pParent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(pParent != nullptr);

  pParent->on_mouse_move(x, y);
}

void GLWindow::Impl::mouse_enter_leave(GLFWwindow* ptr_window, int entered)
{
  auto ptr_parent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent != nullptr);

  double x = 0, y = 0;
  glfwGetCursorPos(ptr_window, &x, &y);

  int width = 0, height = 0;
  glfwGetWindowSize(ptr_window, &width, &height);

  if (x < 0)
  {
    x = 0;
  }

  if (y < 0)
  {
    y = 0;
  }

  if (x > width)
  {
    x = width;
  }

  if (y > height)
  {
    y = height;
  }

  ptr_parent->on_mouse_enter_leave(entered != 0, x, y);
}

void GLWindow::Impl::mouse_click(GLFWwindow* ptr_window, int button, int action, int mods)
{
  auto ptr_parent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent != nullptr);

  ptr_parent->on_mouse_click(button, action, mods);
}

void GLWindow::Impl::mouse_wheel(GLFWwindow* ptr_window, double delta_x, double delta_y)
{
  auto ptr_parent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent != nullptr);

  ptr_parent->on_mouse_wheel(delta_x, delta_y);
}

void GLWindow::Impl::keyboard_key(GLFWwindow* ptr_window, int key, int code, int action, int mods)
{
  auto pParent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(pParent != nullptr);

  pParent->on_keyboard_key(key, code, action, mods);

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwTerminate();
    TerminateProcess(GetCurrentProcess(), 0); // TODO: Vic. Recheck.
  }
}

void GLWindow::Impl::keyboard_char(GLFWwindow* ptr_window, unsigned int code)
{
  auto ptr_parent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent != nullptr);

  ptr_parent->on_keyboard_char(code);
}

void GLWindow::Impl::drag_drop(GLFWwindow* ptr_window, int count, const char** pptr_paths)
{
  auto ptr_parent = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent != nullptr);

  std::vector<std::string> paths;
  paths.reserve(count);

  for (int i = 0; i < count; i++)
  {
    paths.push_back(pptr_paths[i]);
  }

  ptr_parent->on_drag_drop(paths);
}

void GLWindow::Impl::project(int width, int height)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  width  = width  == 0 ? 1 : width;
  height = height == 0 ? 1 : height;

  GLfloat aspect = GLfloat(width) / GLfloat(height);

  if (width >= height)
  {
    gluOrtho2D(-1.0 * aspect, +1.0 * aspect, -1.0, +1.0);
  }
  else
  {
    gluOrtho2D(-1.0, +1.0, -1.0 / aspect, +1.0 / aspect);
  }

  glMatrixMode(GL_MODELVIEW);

  glViewport(0, 0, width, height);
}

int GLWindow::Impl::create()
{
  glfwSetErrorCallback(error);

  // initialize the GLFW library

  if (!glfwInit())
  {
    Utils::log("GLFW -> glfwInit");
    return __LINE__;
  }

  // setup OpenGL attributes that run-time using in the application

  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // create a hidden window and re-sizable

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  m_ptr_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
  if (m_ptr_window == nullptr)
  {
    Utils::log("GLFW -> glfwCreateWindow");
    return __LINE__;
  }

  // store this parent object to the window

  glfwSetWindowUserPointer(m_ptr_window, this);

  // set the window at center screen then show it

  auto ptr_monitor = glfwGetPrimaryMonitor();
  auto ptr_mode = glfwGetVideoMode(ptr_monitor);
  glfwSetWindowPos(m_ptr_window, (ptr_mode->width - m_width) / 2, (ptr_mode->height - m_height) / 2);

  glfwShowWindow(m_ptr_window);

  // set callback function for resizing and keyboard event

  glfwSetWindowSizeCallback(m_ptr_window, resize);

  glfwSetCursorPosCallback(m_ptr_window, mouse_move);
  glfwSetCursorEnterCallback(m_ptr_window, mouse_enter_leave);
  glfwSetMouseButtonCallback(m_ptr_window, mouse_click);
  glfwSetScrollCallback(m_ptr_window, mouse_wheel);

  glfwSetKeyCallback(m_ptr_window, keyboard_key);
  glfwSetCharCallback(m_ptr_window, keyboard_char);

  glfwSetDropCallback(m_ptr_window, drag_drop);

  // make the window as the current OpenGL context and set swapping interval

  glfwMakeContextCurrent(m_ptr_window);

  glfwSwapInterval(1);

  // initialize the GLEW library

  auto ret = glewInit();
  if (ret != GLEW_OK)
  {
    Utils::log("GLFW -> glewInit");;
    return __LINE__;
  }

  // logging several OpenGL information

  auto renderer = glGetString(GL_RENDERER);
  Utils::log("Renderer: %s", renderer);

  auto version = glGetString(GL_VERSION);
  Utils::log("OpenGL Version: %s", version);

  int n = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &n);
  m_extensions.reserve(n);
  for (int i = 0; i < n; ++i)
  {
    auto s = (char*)glGetStringi(GL_EXTENSIONS, i);
    m_extensions.push_back(s);
  }

  const auto s = wglGetExtensionsStringARB(wglGetCurrentDC());
  m_arb_extensions = Utils::split_string_t<std::string>(s, " ");

  // setup window view port

  project(m_width, m_height);

  return 0;
}

int GLWindow::Impl::destroy()
{
  if (m_ptr_window == nullptr)
  {
    glfwDestroyWindow(m_ptr_window);
    glfwTerminate();
  }

  // terminate process // TODO: Vic. Recheck.

  return 0;
}

int GLWindow::Impl::run()
{
  if (this->create() != 0)
  {
    return __LINE__;
  }

  // Initialize before drawing

  m_ptr_parent->initial();

  while (glfwWindowShouldClose(m_ptr_window) == GLFW_FALSE)
  {
    this->on_display();

    glfwPollEvents();
    glfwSwapBuffers(m_ptr_window);
  }

  // finalize after drawing

  m_ptr_parent->final();

  // destroy the window then terminate the application

  if (this->destroy() != 0)
  {
    return __LINE__;
  }

  return 0;
}

/**
 * CGLWindow
 */

GLWindow::GLWindow(const std::string& name, int width, int height, color_t bg)
{
  m_ptr_impl = new GLWindow::Impl(this, name, width, height, bg);
}

GLWindow::~GLWindow()
{
  delete m_ptr_impl;
}

void GLWindow::initial()
{
  // OVERRIDABLE
}

void GLWindow::final()
{
  // OVERRIDABLE
}

void GLWindow::on_display()
{
  // OVERRIDABLE
}

void GLWindow::on_resize(int width, int height)
{
  // OVERRIDABLE
}

void GLWindow::on_mouse_move(double x, double y)
{
  // OVERRIDABLE
}

void GLWindow::on_mouse_enter_leave(bool Entered, double x, double y)
{
  // OVERRIDABLE
}

void GLWindow::on_mouse_click(int button, int action, int mods)
{
  // OVERRIDABLE
}

void GLWindow::on_mouse_wheel(double delta_x, double delta_y)
{
  // OVERRIDABLE
}

void GLWindow::on_keyboard_key(int key, int code, int action, int mods)
{
  // OVERRIDABLE
}

void GLWindow::on_keyboard_char(unsigned int code)
{
  // OVERRIDABLE
}

void GLWindow::on_drag_drop(const std::vector<std::string>& paths)
{
  // OVERRIDABLE
}

void GLWindow::run()
{
  if (m_ptr_impl->run() != 0)
  {
    throw "Initialize GL Failed";
  }
}

const std::vector<std::string>& GLWindow::extensions() const
{
  return m_ptr_impl->m_extensions;
}

const std::vector<std::string>& GLWindow::arb_extensions() const
{
  return m_ptr_impl->m_arb_extensions;
}

GLFWwindow* GLWindow::ptr_window()
{
  return m_ptr_impl->m_ptr_window;
}
