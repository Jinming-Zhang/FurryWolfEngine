#pragma once
namespace WEngine
{
  class FurryWolfEngine;
  class GameObject;
  class TransformComponent;
  class Component
  {
    friend class GameObject;

  protected:
    FurryWolfEngine *engine;

  public:
    GameObject *gameObject;
    TransformComponent *transform;

  public:
    Component() {}
    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update(float deltaTime) {}
    virtual void FixedUpdate(float fixedDeltaTime) {}
    virtual void LateUpdate(float deltaTime) {}
    ~Component() {}

    // template <typename T>
    // T *AddComponent()
    // {
    //   return gameObject->AddComponent<T>();
    // }
  };

}
