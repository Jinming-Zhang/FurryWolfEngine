#pragma once
#include <string>
#include <functional>
#include "IWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class WolfGlfwWindow : public IWindow
{
private:
  GLFWwindow *window;
  static int WIDTH;
  static int HEIGHT;

public:
  WolfGlfwWindow();
  ~WolfGlfwWindow();
  virtual bool Init(int width, int height, const std::string &title) override;
  virtual bool ShouldClose() override;
  virtual void SwapBuffers() override;
  virtual void Destroy() override;
  virtual void PollEvents() override;

public:
  // getters
  virtual int GetWidth() override;
  virtual int GetHeight() override;
};
