#pragma once
namespace WEngine
{
  class GameObject;
  class FurryWolfEngine;
  class Component
  {
    friend class GameObject;

  protected:
    GameObject *gameObject;
    FurryWolfEngine *engine;

  public:
    Component() {}
    virtual void Awake(){}
    virtual void Start(){}
    virtual void Update(float deltaTime) {}
    virtual void FixedUpdate(float fixedDeltaTime) {}
    virtual void LateUpdate(float deltaTime) {}
    ~Component() {}
  };

}
