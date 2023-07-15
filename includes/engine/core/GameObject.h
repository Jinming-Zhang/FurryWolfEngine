#pragma once
#include <vector>
namespace WEngine
{
  class Component;
  class GameObject
  {
  private:
    std::vector<Component *> components;

  public:
    GameObject() {}
    virtual void Update(float deltaTime) {}
    virtual void FixedUpdate(float fixedDeltaTime) {}
    virtual void LateUpdate(float deltaTime) {}
    template <typename T>
    T *AddComponent()
    {
      T *cmp = new T();
      components.push_back(cmp);
    }
    ~GameObject() {}
  };
}
