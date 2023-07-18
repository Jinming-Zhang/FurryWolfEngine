#pragma once
namespace WEngine
{
  class GameObject;
  class Component
  {
    friend class GameObject;

  protected:
    GameObject *gameObject;

  public:
    Component() {}
    virtual void Update(float deltaTime) {}
    virtual void FixedUpdate(float fixedDeltaTime) {}
    virtual void LateUpdate(float deltaTime) {}
    ~Component() {}
  };

}
