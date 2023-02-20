/**
 * @file   glwnd.cpp
 * @author Vic P.
 * @brief  GL Window
 */

#include "glwnd/glwnd.h"
#include "glwnd/utils.h"
#include "glwnd/text.h"
#include "glwnd/view.h"
#include "glwnd/layout.h"
#include "glwnd/viewport.h"
#include "glwnd/primitive.h"

#include "debug.inl"

#include <gl/glew.h>
#include <gl/wglew.h>
#include <glfw/glfw3.h>

#include "3rdparty/imgui-1.82/backends/imgui_impl_glfw.h"
#include "3rdparty/imgui-1.82/backends/imgui_impl_opengl3.h"

#include <Windows.h>
#include <cassert>
#include <chrono>
#include <functional>

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
  void on_resize(int width, int height);

  void on_mouse_move(int x, int y);
  void on_mouse_enter_leave(bool entered, int x, int y);
  void on_mouse_click(int button, int action, int mods, int x, int y);
  void on_mouse_wheel(int dx, int dy);

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
  static void mouse_wheel(GLFWwindow* ptr_window, double dx, double dy);

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
  void toggle_fullscreen();
  GLLayout& layout();
  void set_layout(GLLayout* ptr_layout);
  p2i  get_current_mouse_position(bool* ptr_outside = nullptr);
  GLFWmonitor* get_ptr_current_monitor(GLFWwindow* ptr_window);
  void iterate_views(std::function<void(GLView& view)> fn);
  void set_default_icon();

private:
  GLWindow&   m_parent;
  GLFWwindow* m_ptr_window;
  GLViewPort* m_ptr_current_viewport;

  std::unique_ptr<GLLayout> m_ptr_layout;

  int m_width;
  int m_height;
  color_t m_bg;
  std::string m_name;

  std::vector<std::string> m_extensions;
  std::vector<std::string> m_arb_extensions;

  bool m_debug_enabled;
  bool m_dear_imgui_enabled;
  dear_imgui_cfg m_dear_imgui_cfg;
};

GLWindow::Impl::Impl(GLWindow& parent, const std::string& name, int width, int height, color_t bg)
  : m_parent(parent)
  , m_ptr_window(nullptr), m_ptr_layout(nullptr), m_ptr_current_viewport(nullptr)
  , m_name(name), m_width(width), m_height(height), m_bg(bg)
  , m_debug_enabled(false)
  , m_dear_imgui_enabled(false)
{
  m_ptr_current_viewport = new GLViewPort();
  m_ptr_layout = GLLayout::_empty(parent);
}

GLWindow::Impl::~Impl()
{
  delete m_ptr_current_viewport;
}

void GLWindow::Impl::on_display()
{
  this->iterate_views([&](GLView& view)
  {
    view.on_display();
  });
}

void GLWindow::Impl::on_resize(int width, int height)
{
  this->iterate_views([&](GLView& view)
  {
    auto& win = view.viewport().coordinate().win;
    view.on_resize(win.width(), win.height());
  });
}

void GLWindow::Impl::on_mouse_move(int x, int y)
{
  this->iterate_views([&](GLView& view)
  {
    auto& win = view.viewport().coordinate().win;
    if (utils::is_point_inside_rect(p2i(x, y), win))
    {
      auto v = view.viewport().win_to_vpc(p2i(x, y));
      x = v.x();
      y = v.y();
      view.on_mouse_move(x, y);
    }
  });
}

void GLWindow::Impl::on_mouse_enter_leave(bool entered, int x, int y)
{
  this->iterate_views([&](GLView& view)
  {
    auto& win = view.viewport().coordinate().win;
    if (utils::is_point_inside_rect(p2i(x, y), win))
    {
      auto v = view.viewport().win_to_vpc(p2i(x, y));
      x = v.x();
      y = v.y();
      view.on_mouse_enter_leave(entered, x, y);
    }
  });
}

void GLWindow::Impl::on_mouse_click(int button, int action, int mods, int x, int y)
{
  this->iterate_views([&](GLView& view)
  {
    auto& win = view.viewport().coordinate().win;
    if (utils::is_point_inside_rect(p2i(x, y), win))
    {
      auto v = view.viewport().win_to_vpc(p2i(x, y));
      x = v.x();
      y = v.y();
      view.on_mouse_click(button, action, mods, x, y);
    }
  });
}

void GLWindow::Impl::on_mouse_wheel(int dx, int dy)
{
  this->iterate_views([&](GLView& view)
  {
    view.on_mouse_wheel(dx, dy);
  });
}

void GLWindow::Impl::on_keyboard_key(int key, int code, int action, int mods)
{
  this->iterate_views([&](GLView& view)
  {
    view.on_keyboard_key(key, code, action, mods);
  });
}

void GLWindow::Impl::on_keyboard_char(unsigned int code)
{
  this->iterate_views([&](GLView& view)
  {
    view.on_keyboard_char(code);
  });
}

void GLWindow::Impl::on_drag_drop(const std::vector<std::string>& paths)
{
  this->iterate_views([&](GLView& view)
  {
    view.on_drag_drop(paths);
  });
}

void GLWindow::Impl::error(int code, const char* description)
{
  utils::log("GLFW -> %d, %s", code, description);
}

void GLWindow::Impl::mouse_move(GLFWwindow* ptr_window, double, double)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  const auto v = ptr_parent_impl->get_current_mouse_position();

  ptr_parent_impl->on_mouse_move(v.x(), v.y());
}

void GLWindow::Impl::mouse_enter_leave(GLFWwindow* ptr_window, int entered)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  const auto v = ptr_parent_impl->get_current_mouse_position();

  ptr_parent_impl->on_mouse_enter_leave(entered != 0, v.x(), v.y());
}

void GLWindow::Impl::mouse_click(GLFWwindow* ptr_window, int button, int action, int mods)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  const auto v = ptr_parent_impl->get_current_mouse_position();

  ptr_parent_impl->on_mouse_click(button, action, mods, v.x(), v.y());
}

void GLWindow::Impl::mouse_wheel(GLFWwindow* ptr_window, double dx, double dy)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->on_mouse_wheel(int(dx), int(dy));
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
    paths.emplace_back(pptr_paths[i]);
  }

  ptr_parent_impl->on_drag_drop(paths);
}

void GLWindow::Impl::set_layout(GLLayout* ptr_layout)
{
  assert(ptr_layout != nullptr);
  m_ptr_layout.reset(ptr_layout);
}

GLLayout& GLWindow::Impl::layout()
{
  return *(m_ptr_layout.get());
}

int GLWindow::Impl::create()
{
  glfwSetErrorCallback(error);

  // initialize the GLFW library

  if (!glfwInit())
  {
    utils::log("GLFW -> glfwInit");
    return __LINE__;
  }

  // configure OpenGL like require a minimum version, forward compatible, etc
  // for run-time using in the application
  // https://www.glfw.org/docs/latest/window_guide.html#window_hints

  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // enable anti aliasing 4x MSAA

  glfwWindowHint(GLFW_SAMPLES, 4);

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
    utils::log("GLFW -> glfwCreateWindow");
    return __LINE__;
  }

  // generate and set default icon

  this->set_default_icon();

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

  // turn-on v-sync (for enabled double-buffer)

  glfwSwapInterval(1);

  // initialize the GLEW library

  auto ret = glewInit();
  if (ret != GLEW_OK)
  {
    utils::log("GLFW -> glewInit");
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
  utils::log("Vendor: %s", vendor);

  auto renderer = glGetString(GL_RENDERER);
  utils::log("Renderer: %s", renderer);

  auto version = glGetString(GL_VERSION);
  utils::log("OpenGL Version: %s", version);

  int n = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &n);
  m_extensions.reserve(n);
  for (int i = 0; i < n; ++i)
  {
    auto s = (char*)glGetStringi(GL_EXTENSIONS, i);
    m_extensions.emplace_back(s);
  }

  const auto s = wglGetExtensionsStringARB(wglGetCurrentDC());
  m_arb_extensions = utils::split_string_t<std::string>(s, " ");

  // setup default layout

  if (m_ptr_layout == nullptr || m_ptr_layout->views().empty())
  {
    this->set_layout(GLLayout::_1x1(m_parent).release());
  }

  // setup window view-port

  this->iterate_views([&](GLView& view)
  {
    view.setup(*m_ptr_current_viewport, m_width, m_height);
  });

  // setup render for primitive

  this->iterate_views([&](GLView& view)
  {
    view.initialize(&view);
  });

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
  glDepthMask(GL_TRUE);
  // glDepthFunc(GL_EQUAL);

  glEnable(GL_STENCIL_TEST);
  glStencilMask(0xFF);
  // glStencilFunc(GL_EQUAL, 1, 0xFF);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  this->clear(); // set default background color

  m_parent.initial();

  return 0;
}

int GLWindow::Impl::final()
{
  m_parent.final();

  return 0;
}

void GLWindow::Impl::resize(GLFWwindow* ptr_window, int width, int height)
{
  auto ptr_parent_impl = reinterpret_cast<GLWindow::Impl*>(glfwGetWindowUserPointer(ptr_window));
  assert(ptr_parent_impl != nullptr);

  ptr_parent_impl->m_width = width;
  ptr_parent_impl->m_height = height;

  ptr_parent_impl->on_resize(ptr_parent_impl->m_width, ptr_parent_impl->m_height);

  ptr_parent_impl->display();

  glfwPollEvents();
  glfwSwapBuffers(ptr_window);
}

int GLWindow::Impl::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  this->iterate_views([&](GLView& view)
  {
    view.setup(*m_ptr_current_viewport, m_width, m_height);

    // display fps if enabled
     
    if (view.m_fps_enabled)
    {
      view.display_fps();
    }

    // display drawing coordinates

    if (view.m_coordiates_enabled)
    {
      view.viewport().display_coordiates();
    }

    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    {
      // create a new imgui frame

      if (m_dear_imgui_enabled)
      {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
      }

      // display drawing content

      view.on_display();

      // render on the created imgui frame

      if (m_dear_imgui_enabled)
      {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      }
    }
    glPopAttrib();
    glPopMatrix();
  });

  glFlush();

  return 0;
}

int GLWindow::Impl::run()
{
  // create renderer context for drawing

  if (this->create() != 0)
  {
    return __LINE__;
  }

  // initialize before drawing

  this->initial();

  this->iterate_views([&](GLView& view)
  {
    view.initial();
  });

  // install renderer context for imgui framework

  if (m_dear_imgui_enabled)
  {
    this->imgui_create();
  }

  while (glfwWindowShouldClose(m_ptr_window) == GLFW_FALSE)
  {
    // display drawing content

    this->display();

    // polling events & swapping buffer

    glfwPollEvents();
    glfwSwapBuffers(m_ptr_window);
  }

  // uninstall renderer context for imgui framework

  if (m_dear_imgui_enabled)
  {
    this->imgui_destroy();
  }

  // finalize after drawing

  this->iterate_views([&](GLView& view)
  {
    view.final();
  });

  this->final();

  // destroy renderer context and clean-up resources of drawing

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

  switch (m_dear_imgui_cfg.style)
  {
  case dear_imgui_cfg::styles::IMGUI_DARK:
    ImGui::StyleColorsDark();
    break;

  case dear_imgui_cfg::styles::IMGUI_LIGHT:
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

  if (!m_dear_imgui_cfg.font_path.empty() && m_dear_imgui_cfg.font_size > 0.F)
  {
    io.Fonts->AddFontFromFileTTF(m_dear_imgui_cfg.font_path.c_str(), m_dear_imgui_cfg.font_size);
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
void GLWindow::Impl::clear(color_t* pbg)
{
  glcolor_t<GLclampf> bg(pbg != nullptr ? *pbg : m_bg);
  glClearColor(bg.r, bg.g, bg.b, bg.a);
  glClearDepth(1.F);
  glClearStencil(0);
}

void GLWindow::Impl::toggle_fullscreen()
{
  auto ptr_current_monitor = this->get_ptr_current_monitor(m_ptr_window);
  assert(ptr_current_monitor != nullptr);

  auto ptr_video_mode = glfwGetVideoMode(ptr_current_monitor);
  assert(ptr_video_mode != nullptr);

  static bool fullscreen = false;
  fullscreen = !fullscreen;

  static r4i backup;
  int x = 0, y = 0, w = 0, h = 0;

  if (fullscreen)
  {
    // backup the position/size of the current window that being in windowed mode
    glfwGetWindowPos(m_ptr_window, &x, &y);
    glfwGetWindowSize(m_ptr_window, &w, &h);
    backup.set(x, y, x + w, y + h);

    // get the position/size of the current screen
    x = 0;
    y = 0;
    w = ptr_video_mode->width;
    h = ptr_video_mode->height;

    // set the current window to full-screen mode
    glfwSetWindowMonitor(m_ptr_window, ptr_current_monitor, x, y, w, h, GLFW_DONT_CARE);
  }
  else // windowed
  {
    // restore the position/size of the current window that previously in windowed mode
    const auto origin = backup.origin();
    x = origin.x();
    y = origin.y();
    w = backup.width();
    h = backup.height();

    // set the current window to the previous position/size that in windowed mode
    glfwSetWindowMonitor(m_ptr_window, nullptr, x, y, w, h, GLFW_DONT_CARE);
  }
}

GLFWmonitor* GLWindow::Impl::get_ptr_current_monitor(GLFWwindow* ptr_window)
{
  if (ptr_window == nullptr)
  {
    return nullptr;
  }

  int num_monitors = 0;
  auto pptr_monitors = glfwGetMonitors(&num_monitors);
  if (pptr_monitors == nullptr || num_monitors == 0)
  {
    return nullptr;
  }
  
  int wx = 0, wy = 0, ww = 0, wh = 0;
  glfwGetWindowPos(ptr_window, &wx, &wy);
  glfwGetWindowSize(ptr_window, &ww, &wh);

  GLFWmonitor* ptr_monitor = nullptr;
  int overlap = 0, best_overlap = 0;

  for (int i = 0; i < num_monitors; i++)
  {
    auto ptr_video_mode = glfwGetVideoMode(pptr_monitors[i]);
    if (ptr_video_mode != nullptr)
    {
      int mx, my, mw, mh;
      glfwGetMonitorPos(pptr_monitors[i], &mx, &my);
      mw = ptr_video_mode->width;
      mh = ptr_video_mode->height;

      int overlap =\
        glwnd_max(0, glwnd_min(wx + ww, mx + mw) - glwnd_max(wx, mx)) *
        glwnd_max(0, glwnd_min(wy + wh, my + mh) - glwnd_max(wy, my));

      if (best_overlap < overlap)
      {
        best_overlap = overlap;
        ptr_monitor  = pptr_monitors[i];
      }
    }
  }

  return ptr_monitor;
}

p2i GLWindow::Impl::get_current_mouse_position(bool* ptr_outside)
{
  assert(m_ptr_window != nullptr);

  bool outside = false;

  double x = 0., y = 0.;

  glfwGetCursorPos(m_ptr_window, &x, &y);

  int width = 0, height = 0;
  glfwGetWindowSize(m_ptr_window, &width, &height);

  y = height - y; // cuz win coordinate fipped

  if (x < 0)
  {
    x = 0;
    outside = true;
  }

  if (x > width)
  {
    x = width;
    outside = true;
  }

  if (y < 0)
  {
    y = 0;
    outside = true;
  }

  if (y > height)
  {
    y = height;
    outside = true;
  }

  if (ptr_outside != nullptr)
  {
    *ptr_outside = outside;
  }

  return p2i(int(x), int(y));
}

void GLWindow::Impl::iterate_views(std::function<void(GLView& view)> fn)
{
  for (auto& ptr_view : m_ptr_layout->views())
  {
    ptr_view->setup(*m_ptr_current_viewport, m_width, m_height);
    fn(*ptr_view);
  }
}

void GLWindow::Impl::set_default_icon()
{
  assert(m_ptr_window != nullptr);

  const size_t icon_color = 1;
  const size_t icon_size  = 16;
  const size_t icon_pixel_format = 4;

  const char* const data[] =
  {
      "0000000000000000",
      "0..............0",
      "0..00000.0.....0",
      "0..0.....0.....0",
      "0..0.000.0.....0",
      "0..0...0.0.....0",
      "0..00000.0000..0",
      "0..............0",
      "0..............0",
      "0..0...0.000...0",
      "0..0...0.0..0..0",
      "0..0.0.0.0..0..0",
      "0..0.0.0.0..0..0",
      "0..00000.000...0",
      "0..............0",
      "0000000000000000"
  };

  const byte_t colors[6][icon_pixel_format] =
  {
      { 0x00, 0x00, 0x00, 0x00 }, // transparent
      { 0xFF, 0xFF, 0xFF, 0xFF }, // white
      { 0x00, 0x00, 0x00, 0xFF }, // black
      { 0xFF, 0x00, 0x00, 0xFF }, // red
      { 0x00, 0xFF, 0x00, 0xFF }, // green
      { 0x00, 0x00, 0xFF, 0xFF }, // blue
  };

  byte_t  icon_pixels[icon_size * icon_size * icon_pixel_format];
  byte_t* ptr = icon_pixels;

  for (size_t row = 0; row < icon_size; row++)
  {
    for (size_t col = 0; col < icon_size; col++, ptr += icon_pixel_format)
    {
      const auto pixel = data[row][col] == '0' ? colors[icon_color] : colors[0];
      memcpy(ptr, pixel, icon_pixel_format);
    }
  }

  GLFWimage icon = { icon_size, icon_size, icon_pixels };

  glfwSetWindowIcon(m_ptr_window, 1, &icon);
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

GLLayout& GLWindow::set_layout(GLLayout* ptr_layout)
{
  m_ptr_impl->set_layout(ptr_layout);
  return this->layout();
}

GLLayout& GLWindow::layout()
{
  return m_ptr_impl->layout();
}

void GLWindow::toggle_fullscreen()
{
  m_ptr_impl->toggle_fullscreen();
}

void GLWindow::enable_debug(bool state)
{
  m_ptr_impl->m_debug_enabled = state;
}

void GLWindow::enable_dear_imgui(bool state, dear_imgui_cfg* ptr_dear_imgui_cfg)
{
  m_ptr_impl->m_dear_imgui_enabled = state;

  if (ptr_dear_imgui_cfg != nullptr)
  {
    m_ptr_impl->m_dear_imgui_cfg.style = ptr_dear_imgui_cfg->style;
    m_ptr_impl->m_dear_imgui_cfg.font_path = ptr_dear_imgui_cfg->font_path;
    m_ptr_impl->m_dear_imgui_cfg.font_size = ptr_dear_imgui_cfg->font_size;
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

}; // glwnd