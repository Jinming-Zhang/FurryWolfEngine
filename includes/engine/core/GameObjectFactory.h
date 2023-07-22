#pragma once
namespace WEngine
{
  class GameObject;
  class FurryWolfEngine;
  class GameObjectFactory
  {
  private:
  public:
    GameObjectFactory(/* args */);
    ~GameObjectFactory();
    static GameObject *CreatePointLightGo(FurryWolfEngine *engine);
  };
}
