#pragma once
#include <string>
#include <utility>
class IWindow
{
private:
public:
  IWindow(){};
  virtual ~IWindow(){};
  virtual bool Init(int width, int height, const std::string &title) = 0;
  virtual void Destroy() = 0;

  // inputs
  virtual bool IsKeyPressed(int keyCode) = 0;
  virtual bool IsKeyReleased(int keyCode) = 0;
  virtual void SetInputMode(int mode, int value) = 0;
  virtual std::pair<float, float> GetMousePosition() = 0;

  virtual bool ShouldClose() = 0;
  virtual void SwapBuffers() = 0;
  virtual void PollEvents() = 0;

  // getter / setters
  virtual int GetWidth() = 0;
  virtual int GetHeight() = 0;
};
