#include "engine/core/GameObject.h"
#include "engine/components/Component.h"

namespace WEngine
{
  GameObject::GameObject()
  {
    components = std::vector<std::unique_ptr<Component>>();
  }

  void GameObject::Update(float deltaTime)
  {
    for (auto &com : components)
    {
      com->Update(deltaTime);
    }
  }
  void GameObject::FixedUpdate(float fixedDeltaTime)
  {
    for (auto &com : components)
    {
      com->FixedUpdate(fixedDeltaTime);
    }
  }
  void GameObject::LateUpdate(float deltaTime)
  {
    for (auto &com : components)
    {
      com->LateUpdate(deltaTime);
    }
  }
}
