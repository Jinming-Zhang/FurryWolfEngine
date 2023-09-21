#pragma once
#include <vector>
#include "engine/core/GameObject.h"
namespace WEngine
{
  class GameObject;
  class FurryWolfEngine;
  class Scene
  {
    friend class SceneMaker;

  private:
    std::vector<GameObject *> gameobjects;
    FurryWolfEngine *engine;
    void CreateDefaultScene();

  public:
    Scene(FurryWolfEngine *engine);
    ~Scene();
    void AddGameObject(GameObject *gameobject);
    void Load();
    void Start();
    void Refresh(float deltaTime);
    void DestroyScene();

    template <typename T>
    GameObject *FindObjectOfType()
    {
      for (auto go : gameobjects)
      {
        if (go->GetComponent<T>() != nullptr)
        {
          return go;
        }
      }
      return nullptr;
    }
  };

}
