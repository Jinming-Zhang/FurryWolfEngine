#pragma once
#include <utility>
#include "GLFW/glfw3.h"
#include "engine/window/IWindow.h"
namespace WEngine
{
  class InputSystem
  {
  private:
    IWindow *window;
    static InputSystem *instance;
    InputSystem();

  private:
    std::pair<float, float> prevMousePos;
    std::pair<float, float> currMousePos;

  public:
    static float DeltaTime;

  public:
    static InputSystem *Instance();
    void SetWindowContext(IWindow *windowContext);
    void Update();
    void SetInputMode(int mode, int value);
    bool KeyPressed(int key);
    bool KeyReleased(int key);

    std::pair<float, float> GetMousePosition();
    std::pair<float, float> GetMousePositionDelta();

    ~InputSystem();
  };

}
