#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "engine/components/Component.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/PointLightComponent.h"
#include "engine/components/SpotLightComponent.h"

namespace WEngine
{
  class GameObject
  {
    friend class FurryWolfEngine;

  private:
    static int idCounter;

  private:
    FurryWolfEngine *engine;
    std::vector<std::unique_ptr<Component>> components;
    std::string name;
    GameObject(std::string name = "GameObject_" + std::to_string(++idCounter));

  public:
    static GameObject *CreateGameObject(std::string name = "");
    virtual void Rename(const std::string &name) { this->name = name; }
    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update(float deltaTime);
    virtual void FixedUpdate(float fixedDeltaTime);
    virtual void LateUpdate(float deltaTime);
    virtual void Render();
    virtual void Destroy();
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
    template <typename T>
    T *AddComponent()
    {
      std::unique_ptr<T> cmp = std::make_unique<T>();
      if (Component *c = dynamic_cast<Component *>(cmp.get()))
      {
        c->gameObject = this;
        c->engine = engine;
        if (TransformComponent *transform = GetComponent<TransformComponent *>())
        {
          c->transform = transform;
        }
        else
        {
          std::cout << "Cannot find transform component on gameobject!\n";
        }
      }
      components.push_back(std::move(cmp));
      return (T *)components[components.size() - 1].get();
    }
    virtual ~GameObject() {}

#ifdef WINDOWS
    template <>
    TransformComponent *AddComponent<TransformComponent>()
    {
      std::unique_ptr<TransformComponent> cmp = std::make_unique<TransformComponent>();
      cmp->gameObject = this;
      cmp->engine = engine;
      cmp->transform = cmp.get();
      components.push_back(std::move(cmp));
      return (TransformComponent *)components[components.size() - 1].get();
    }

    template <>
    PointLightComponent *AddComponent<PointLightComponent>()
    {
      std::unique_ptr<PointLightComponent> cmp = std::make_unique<PointLightComponent>();
      cmp->gameObject = this;
      cmp->engine = engine;
      cmp->transform = GetComponent<TransformComponent *>();
      ++PointLightComponent::PointLightIndexer;
      components.push_back(std::move(cmp));
      return (PointLightComponent *)components[components.size() - 1].get();
    }

    template <>
    SpotLightComponent *AddComponent<SpotLightComponent>()
    {
      std::unique_ptr<SpotLightComponent> cmp = std::make_unique<SpotLightComponent>();
      cmp->gameObject = this;
      cmp->engine = engine;
      cmp->transform = GetComponent<TransformComponent *>();
      ++SpotLightComponent::SpotLightIndexer;
      components.push_back(std::move(cmp));
      return (SpotLightComponent *)components[components.size() - 1].get();
    }
#endif // WINDOWS
  };
}
