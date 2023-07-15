#include <vector>
#include "engine/core/FurryWolfEngine.h"
#include "engine/core/GameObject.h"
namespace WEngine
{
  FurryWolfEngine::FurryWolfEngine()
  {
    gameobjects = std::vector<GameObject *>();
  }

  FurryWolfEngine::~FurryWolfEngine() {}

  void WEngine::FurryWolfEngine::CreateGameObject()
  {
    GameObject *go = new GameObject();
    gameobjects.push_back(go);
  }
}
