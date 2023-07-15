#pragma once
class Component
{
private:
  /* data */
public:
  Component() {}
  virtual void Update(float deltaTime) {}
  virtual void FixedUpdate(float fixedDeltaTime) {}
  virtual void LateUpdate(float deltaTime) {}
  ~Component() {}
};
