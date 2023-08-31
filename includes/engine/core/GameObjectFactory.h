#pragma once
namespace WEngine
{
  class GameObject;
  class FurryWolfEngine;
  class GameObjectFactory
  {
  private:
  public:
    GameObjectFactory() = delete;
    ~GameObjectFactory();
    static GameObject *CreatePointLightGo(FurryWolfEngine *engine);
    static GameObject *CreatePlaneMeshGO(FurryWolfEngine *engine);
    static GameObject *CreateCubeMeshGO(FurryWolfEngine *engine);
  };
}
