/**
 * @file   glwnd.cpp
 * @author Vic P.
 * @brief  GL Window
 */

#include "glwnd/glwnd.h"
#include "glwnd/utils.h"
#include "glwnd/text.h"

#include "debug.inl"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include "imgui-1.82/backends/imgui_impl_glfw.h"
#include "imgui-1.82/backends/imgui_impl_opengl3.h"

#include <Windows.h>
#include <cassert>
#include <chrono>

/**
 * CGLWindow - Implementation
 */

namespace glwnd
{

class GLWindow::Impl
{
  friend GLWindow;

public:
  Impl(GLWindow& parent, const std::string& name, int width, int height, color_t bg);
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

public:
  int  run();
  void clear(color_t* pbg = nullptr);

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

private:
  int create();
  int destroy();
  int initial();
  int final();
  int display();

  void imgui_create();
  void imgui_destroy();

  void display_fps();

private:
  GLWindow& m_parent;
  GLFWwindow* m_ptr_window;
  GLViewPort* m_ptr_viewport;

  std::string m_name;
  int m_width;
  int m_height;
  color_t m_bg;

  int m_fps;
  TextRender2D m_text_render_fps;

  std::vector<std::string> m_extensions;
  std::vector<std::string> m_arb_extensions;

  bool m_debug_enabled;
  bool m_fps_enabled;
  bool m_coordiates_enabled;

  bool m_imgui_enabled;
  imgui_cfg m_imgui_cfg;
};

GLWindow::Impl::Impl(GLWindow& parent, const std::string& name, int width, int height, color_t bg)
  : m_ptr_window(nullptr), m_ptr_viewport(nullptr), m_parent(parent)
  , m_name(name), m_width(width), m_height(height), m_bg(bg)
  , m_fps_enabled(false), m_fps(0)
  , m_debug_enabled(false)
  , m_imgui_enabled(false)
  , m_coordiates_enabled(false)
{
  m_ptr_viewport = new GLViewPort(m_parent);
}

GLWindow::Impl::~Impl()
{
  delete m_ptr_viewport;
}

void GLWindow::Impl::on_display()
{
  m_parent.on_display();
}

void GLWindow::Impl::on_resize(int width, int height)
{
  m_parent.on_resize(width, height);
}

void GLWindow::Impl::on_mouse_move(double x, double y)
{
  m_parent.on_mouse_move(x, y);
}

void GLWindow::Impl::on_mouse_enter_leave(bool entered, double x, double y)
{
  m_parent.on_mouse_enter_leave(entered, x, y);
}

void GLWindow::Impl::on_mouse_click(int button, int action, int mods)
{
  m_parent.on_mouse_click(button, action, mods);
}

void GLWindow::Impl::on_mouse_wheel(double delta_x, double delta_y)
{
  m_parent.on_mouse_wheel(delta_x, delta_y);
}

void GLWindow::Impl::on_keyboard_key(int key, int code, int action, int mods)
{
  m_parent.on_keyboard_key(key, code, action, mods);
}

void GLWindow::Impl::on_keyboard_char(unsigned int code)
{
  m_parent.on_keyboard_char(code);
}

void GLWindow::Impl::on_drag_drop(const std::vector<std::string>& paths)
{
  m_parent.on_drag_drop(paths);
}

void GLWindow::Impl::error(int code, const char* description)
{
  glwnd::log("GLFW -> %d, %s", code, description);
}

void GLWindow::Impl::resize(GLFWwindow* ptr_window, int width, int height)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->m_width  = width;
  ptr_parent_impl->m_height = height;

  ptr_parent_impl->m_ptr_viewport->setup(ptr_parent_impl->m_width, ptr_parent_impl->m_height);

  ptr_parent_impl->on_resize(ptr_parent_impl->m_width, ptr_parent_impl->m_height);

  ptr_parent_impl->display();

  glfwPollEvents();
  glfwSwapBuffers(ptr_window);
}

void GLWindow::Impl::mouse_move(GLFWwindow* ptr_window, double x, double y)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->on_mouse_move(x, y);
}

void GLWindow::Impl::mouse_enter_leave(GLFWwindow* ptr_window, int entered)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

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

  ptr_parent_impl->on_mouse_enter_leave(entered != 0, x, y);
}

void GLWindow::Impl::mouse_click(GLFWwindow* ptr_window, int button, int action, int mods)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->on_mouse_click(button, action, mods);
}

void GLWindow::Impl::mouse_wheel(GLFWwindow* ptr_window, double delta_x, double delta_y)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->on_mouse_wheel(delta_x, delta_y);
}

void GLWindow::Impl::keyboard_key(GLFWwindow* ptr_window, int key, int code, int action, int mods)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->on_keyboard_key(key, code, action, mods);

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwTerminate();
    TerminateProcess(GetCurrentProcess(), 0); // TODO: Vic. Recheck.
  }
}

void GLWindow::Impl::keyboard_char(GLFWwindow* ptr_window, unsigned int code)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->on_keyboard_char(code);
}

void GLWindow::Impl::drag_drop(GLFWwindow* ptr_window, int count, const char** pptr_paths)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  std::vector<std::string> paths;
  paths.reserve(count);

  for (int i = 0; i < count; i++)
  {
    paths.push_back(pptr_paths[i]);
  }

  ptr_parent_impl->on_drag_drop(paths);
}

int GLWindow::Impl::create()
{
  glfwSetErrorCallback(error);

  // initialize the GLFW library

  if (!glfwInit())
  {
    glwnd::log("GLFW -> glfwInit");
    return __LINE__;
  }

  // configure OpenGL like require a minimum version, forward compatible, etc
  // for run-time using in the application
  // https://www.glfw.org/docs/latest/window_guide.html#window_hints

  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // enable debugging error

  if (m_debug_enabled)
  {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  }

  // create a hidden window and re-sizable

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  m_ptr_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
  if (m_ptr_window == nullptr)
  {
    glwnd::log("GLFW -> glfwCreateWindow");
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
    glwnd::log("GLFW -> glewInit");;
    return __LINE__;
  }

  // enable debugging error context if allows for debug context

  if (m_debug_enabled)
  {
    int flags = 0;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(glDebugOutput, nullptr);
      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
  }

  // logging several OpenGL information

  auto vendor = glGetString(GL_VENDOR);
  glwnd::log("Vendor: %s", vendor);

  auto renderer = glGetString(GL_RENDERER);
  glwnd::log("Renderer: %s", renderer);

  auto version = glGetString(GL_VERSION);
  glwnd::log("OpenGL Version: %s", version);

  int n = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &n);
  m_extensions.reserve(n);
  for (int i = 0; i < n; ++i)
  {
    auto s = (char*)glGetStringi(GL_EXTENSIONS, i);
    m_extensions.push_back(s);
  }

  const auto s = wglGetExtensionsStringARB(wglGetCurrentDC());
  m_arb_extensions = glwnd::split_string_t<std::string>(s, " ");

  // setup window view-port

  m_ptr_viewport->setup(m_width, m_height);

  // set text render for fps

  m_text_render_fps.initialize(&m_parent);

  return 0;
}

int GLWindow::Impl::destroy()
{
  // destroy the window and clean-up resources

  if (m_ptr_window == nullptr)
  {
    glfwDestroyWindow(m_ptr_window);
    glfwTerminate();
  }

  return 0;
}


int GLWindow::Impl::initial()
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  this->clear(); // set default background color

  m_parent.initial();

  return 0;
}

int GLWindow::Impl::final()
{
  m_parent.final();
  return 0;
}

int GLWindow::Impl::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // display fps if enabled

  if (m_fps_enabled)
  {
    display_fps();
  }

  // display drawing coordinates

  if (m_coordiates_enabled)
  {
    m_ptr_viewport->display_coordiates();
  }

  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  {
    // create a new imgui frame

    if (m_imgui_enabled)
    {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
    }

    // display drawing content

    this->on_display();

    // render on the created imgui frame

    if (m_imgui_enabled)
    {
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
  }
  glPopAttrib();
  glPopMatrix();

  glFlush();

  return 0;
}

int GLWindow::Impl::run()
{
  // create context for drawing

  if (this->create() != 0)
  {
    return __LINE__;
  }

  // setup context for the imgui framework

  if (m_imgui_enabled)
  {
    this->imgui_create();
  }

  // initialize before drawing

  this->initial();

  while (glfwWindowShouldClose(m_ptr_window) == GLFW_FALSE)
  {
    // display drawing content

    this->display();

    // polling events & swapping buffer

    glfwPollEvents();
    glfwSwapBuffers(m_ptr_window);
  }

  // finalize after drawing

  this->final();

  // destroy the imgui framework

  if (m_imgui_enabled)
  {
    this->imgui_destroy();
  }

  // destroy the context and clean-up the resources of drawing

  if (this->destroy() != 0)
  {
    return __LINE__;
  }

  return 0;
}

void GLWindow::Impl::imgui_create()
{
  IMGUI_CHECKVERSION();

  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

  // setup style for the imgui framework

  switch (m_imgui_cfg.style)
  {
  case imgui_cfg::styles::IMGUI_DARK:
    ImGui::StyleColorsDark();
    break;

  case imgui_cfg::styles::IMGUI_LIGHT:
    ImGui::StyleColorsLight();
    break;

  default:
    ImGui::StyleColorsClassic();
    break;
  }

  // setup platform/renderer back-end for the imgui framework

  const char* glsl_version = "#version 130";
  ImGui_ImplGlfw_InitForOpenGL(m_ptr_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  if (!m_imgui_cfg.font_path.empty() && m_imgui_cfg.font_size > 0.F)
  {
    io.Fonts->AddFontFromFileTTF(m_imgui_cfg.font_path.c_str(), m_imgui_cfg.font_size);
  }
  else
  {
    io.Fonts->AddFontDefault();
  }
}

void GLWindow::Impl::imgui_destroy()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void GLWindow::Impl::display_fps()
{
  static int fps = 0;
  fps += 1;

  static auto beg_time = std::chrono::high_resolution_clock::now();
  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> delta_time = end_time - beg_time;

  if (delta_time.count() > 1000.0) // 1000ms
  {
    m_fps = fps;
    fps = 0;
    beg_time = std::chrono::high_resolution_clock::now();
  }

  static char fps_text[MAXBYTE] = { 0 };
  sprintf_s(fps_text, "FPS : %d\0", m_fps);

  const int padding = 10;
  const auto& win = m_ptr_viewport->coordinate().win;
  m_text_render_fps.render_text(fps_text, p2i(padding, win.top() - 35 + padding));
}

void GLWindow::Impl::clear(color_t* pbg)
{
  glcolor_t<GLclampf> bg(pbg != nullptr ? *pbg : m_bg);
  glClearColor(bg.r, bg.g, bg.b, bg.a);
  glClearDepth(1.F);
}

/**
 * CGLWindow
 */

GLWindow::GLWindow(const std::string& name, int width, int height, color_t bg)
{
  m_ptr_impl = new GLWindow::Impl(*this, name, width, height, bg);
}

GLWindow::~GLWindow()
{
  delete m_ptr_impl;
}

GLFWwindow& GLWindow::window()
{
  return *(m_ptr_impl->m_ptr_window);
}

GLViewPort& GLWindow::viewport()
{
  return *(m_ptr_impl->m_ptr_viewport);
}

const std::vector<std::string>& GLWindow::extensions() const
{
  return m_ptr_impl->m_extensions;
}

const std::vector<std::string>& GLWindow::arb_extensions() const
{
  return m_ptr_impl->m_arb_extensions;
}

void GLWindow::run()
{
  if (m_ptr_impl->run() != 0)
  {
    throw "Initialize GL Failed";
  }
}

void GLWindow::clear(color_t* pbg)
{
  m_ptr_impl->clear(pbg);
}

void GLWindow::enable_fps(bool state)
{
  m_ptr_impl->m_fps_enabled = state;
}

void GLWindow::enable_debug(bool state)
{
  m_ptr_impl->m_debug_enabled = state;
}

void glwnd::GLWindow::enable_coordiates(bool state)
{
  m_ptr_impl->m_coordiates_enabled = state;
}

void GLWindow::enable_imgui(bool state, imgui_cfg* ptr_imgui_cfg)
{
  m_ptr_impl->m_imgui_enabled = state;

  if (ptr_imgui_cfg != nullptr)
  {
    m_ptr_impl->m_imgui_cfg.style = ptr_imgui_cfg->style;
    m_ptr_impl->m_imgui_cfg.font_path = ptr_imgui_cfg->font_path;
    m_ptr_impl->m_imgui_cfg.font_size = ptr_imgui_cfg->font_size;
  }
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

}; // glwnd