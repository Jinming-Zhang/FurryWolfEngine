#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include "IWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
namespace WEngine
{
  class WolfGlfwWindow : public IWindow
  {
  public:
    enum class KeyState
    {
      PressedThisFrame,
      Hold,
      RelesedThisFrame,
      Relesed
    };

  private:
    GLFWwindow *window;
    static int WIDTH;
    static int HEIGHT;
    static double mouseX;
    static double mouseY;
    static void mouse_callback(GLFWwindow *w, double xpos, double ypos);
    std::unordered_map<int, KeyState> keyStates;
    void InitKeyState(int keyCode, int glfwKeyState);
    void UpdateKeyState(int keyCode);
    void UpdateKeyStateToPressed(int keyCode);
    void UpdateKeyStateToReleased(int keyCode);

  public:
    WolfGlfwWindow();
    ~WolfGlfwWindow();
    virtual bool Init(int width, int height, const std::string &title) override;
    virtual bool ShouldClose() override;
    virtual void SwapBuffers() override;
    virtual void Destroy() override;
    virtual void PollEvents() override;
    virtual bool IsKeyPressed(int keyCode) override;
    virtual bool IsKeyReleased(int keyCode) override;
    virtual std::pair<float, float> GetMousePosition() override;
    virtual void SetInputMode(int mode, int value) override;

  public:
    // getters
    virtual int GetWidth() override;
    virtual int GetHeight() override;
  };
}
