#include "engine/inputs/InputSystem.h"

namespace WEngine
{
  float InputSystem::DeltaTime = .0f;
  void InputSystem::SetWindowContext(IWindow *windowContext)
  {
    this->window = windowContext;
  }

  bool InputSystem::KeyPressed(int key)
  {
    return window->IsKeyPressed(key);
  }

  bool InputSystem::KeyReleased(int key)
  {
    return window->IsKeyReleased(key);
  }

  void InputSystem::Update()
  {
    prevMousePos = currMousePos;
    currMousePos = window->GetMousePosition();
  }

  void InputSystem::SetInputMode(int mode, int value)
  {
    window->SetInputMode(mode, value);
  }

  std::pair<float, float> InputSystem::GetMousePosition()
  {
    return window->GetMousePosition();
  }
  std::pair<float, float> InputSystem::GetMousePositionDelta()
  {
    std::pair<float, float> pos = window->GetMousePosition();
    return std::pair(
        pos.first - prevMousePos.first,
        pos.second - prevMousePos.second);
  }

  InputSystem::InputSystem() { window = nullptr; }
  InputSystem::~InputSystem() {}

  InputSystem *InputSystem::instance = nullptr;
  InputSystem *InputSystem::Instance()
  {
    if (instance == nullptr)
    {
      instance = new InputSystem();
    }
    return instance;
  }
}
