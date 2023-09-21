#include <iostream>
#include "engine/window/WolfGlfwWindow.h"
namespace WEngine
{
  int WolfGlfwWindow::WIDTH{0};
  int WolfGlfwWindow::HEIGHT{0};
  double WolfGlfwWindow::mouseX{0};
  double WolfGlfwWindow::mouseY{0};

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
    glfwSetCursorPosCallback(window, WolfGlfwWindow::mouse_callback);
    WIDTH = width;
    HEIGHT = height;
    keyStates = std::unordered_map<int, KeyState>();
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

  void WolfGlfwWindow::UpdateKeyState(int keyCode)
  {
    int glfwKeyState = glfwGetKey(window, keyCode);

    if (keyStates.find(keyCode) == keyStates.end())
    {
      InitKeyState(keyCode, glfwKeyState);
    }
    else
    {
      if (glfwKeyState == GLFW_PRESS)
      {
        UpdateKeyStateToPressed(keyCode);
      }
      else
      {
        UpdateKeyStateToReleased(keyCode);
      }
    }
  }
  void WolfGlfwWindow::InitKeyState(int keyCode, int glfwKeyState)
  {
    if (glfwKeyState == GLFW_PRESS)
    {
      keyStates[keyCode] = KeyState::PressedThisFrame;
    }
    else
    {
      keyStates[keyCode] = KeyState::RelesedThisFrame;
    }
  }

  void WolfGlfwWindow::UpdateKeyStateToPressed(int keyCode)
  {
    KeyState prevState = keyStates[keyCode];
    switch (prevState)
    {
    case KeyState::RelesedThisFrame:
    case KeyState::Relesed:
      keyStates[keyCode] = KeyState::PressedThisFrame;
      break;
    case KeyState::Hold:
    case KeyState::PressedThisFrame:
      keyStates[keyCode] = KeyState::Hold;
    default:
      break;
    }
  }

  void WolfGlfwWindow::UpdateKeyStateToReleased(int keyCode)
  {
    KeyState prevState = keyStates[keyCode];
    switch (prevState)
    {
    case KeyState::RelesedThisFrame:
    case KeyState::Relesed:
      keyStates[keyCode] = KeyState::Relesed;
      break;
    case KeyState::Hold:
    case KeyState::PressedThisFrame:
      keyStates[keyCode] = KeyState::RelesedThisFrame;
    default:
      break;
    }
  }

  bool WolfGlfwWindow::IsKeyPressed(int keyCode)
  {
    UpdateKeyState(keyCode);

    return keyStates[keyCode] == KeyState::PressedThisFrame;
  }

  bool WolfGlfwWindow::IsKeyReleased(int keyCode)
  {
    UpdateKeyState(keyCode);
    return keyStates[keyCode] == KeyState::RelesedThisFrame;
  }

  void WolfGlfwWindow::SetInputMode(int mode, int value)
  {
    glfwSetInputMode(window, mode, value);
  }

  std::pair<float, float> WolfGlfwWindow::GetMousePosition()
  {
    return std::pair(WolfGlfwWindow::mouseX, WolfGlfwWindow::mouseY);
  }

  void WolfGlfwWindow::mouse_callback(GLFWwindow *w, double xpos, double ypos)
  {
    WolfGlfwWindow::mouseX = xpos;
    WolfGlfwWindow::mouseY = ypos;
  }
}
