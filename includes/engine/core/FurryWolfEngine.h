#pragma once
#include <vector>

namespace WEngine
{
  class GameObject;
  class FurryWolfEngine
  {
  private:
    std::vector<GameObject *> gameobjects;

  public:
    FurryWolfEngine(/* args */);
    ~FurryWolfEngine();
    void CreateGameObject();
  };

}
