#pragma once
#include <vector>
#include <memory>
#include "engine/components/Component.h"

namespace WEngine
{
  class GameObject
  {
    friend class FurryWolfEngine;

  private:
    std::vector<std::unique_ptr<Component>> components;
    FurryWolfEngine *engine;
    GameObject();

  public:
    virtual void Awake(){}
    virtual void Start(){}
    virtual void Update(float deltaTime);
    virtual void FixedUpdate(float fixedDeltaTime);
    virtual void LateUpdate(float deltaTime);
    template <typename T>
    T *AddComponent()
    {
      std::unique_ptr<T> cmp = std::make_unique<T>();
      if (Component *c = dynamic_cast<Component *>(cmp.get()))
      {
        c->gameObject = this;
        c->engine = engine;
      }
      components.push_back(std::move(cmp));
      return (T *)components[components.size() - 1].get();
    }
    template <typename T>
    T GetComponent()
    {
      for (auto &cmp : components)
      {
        if (T tar = dynamic_cast<T>(cmp.get()))
        {
          return tar;
        }
      }
      return nullptr;
    }
    ~GameObject() {}
  };
}
