#include <iostream>
#include "engine/window/WolfGlfwWindow.h"
int WolfGlfwWindow::WIDTH{0};
int WolfGlfwWindow::HEIGHT{0};

WolfGlfwWindow::WolfGlfwWindow() {}
WolfGlfwWindow::~WolfGlfwWindow() {}

bool WolfGlfwWindow::Init(int width, int height, const std::string &title)
{
  if (glfwInit() != GL_TRUE)
  {
    std::cout << "glfwInit failed.\n";
    return false;
  }
  // glfw window config reference:
  // https://www.glfw.org/docs/latest/window.html#window_hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (window == NULL)
  {
    return false;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed initialize glad\n";
    return false;
  }
  glViewport(0, 0, width, height);
  auto lambda = [](GLFWwindow *window, int width, int height)
  {
    glViewport(0, 0, width, height);
  };
  glfwSetFramebufferSizeCallback(window, lambda);
  WIDTH = width;
  HEIGHT = height;
  return true;
}

bool WolfGlfwWindow::ShouldClose()
{
  return glfwWindowShouldClose(window);
}

void WolfGlfwWindow::SwapBuffers()
{
  glfwSwapBuffers(window);
}
void WolfGlfwWindow::Destroy()
{
  glfwTerminate();
}

void WolfGlfwWindow::PollEvents()
{
  glfwPollEvents();
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

int WolfGlfwWindow::GetWidth()
{
  return WIDTH;
}

int WolfGlfwWindow::GetHeight()
{
  return HEIGHT;
}
