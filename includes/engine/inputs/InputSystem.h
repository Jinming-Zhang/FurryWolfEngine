#pragma once
#include "GLFW/glfw3.h"
class InputSystem
{
private:
  GLFWwindow *window;

public:
  InputSystem(GLFWwindow *window);
  bool KeyPressed(int key);
  void Update();
  ~InputSystem();
};

InputSystem::InputSystem(GLFWwindow *window) : window{window} {}

InputSystem::~InputSystem() {}

bool InputSystem::KeyPressed(int key)
{
  return (glfwGetKey(window, key) == GLFW_PRESS);
}
void InputSystem::Update()
{
}
