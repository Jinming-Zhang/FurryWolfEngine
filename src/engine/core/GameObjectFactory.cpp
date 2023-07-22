#include "engine/core/FurryWolfEngine.h"
#include "engine/core/GameObject.h"
#include "engine/core/GameObjectFactory.h"

#include "engine/components/PointLightComponent.h"

namespace WEngine
{
  GameObjectFactory::GameObjectFactory()
  {
  }

  GameObjectFactory::~GameObjectFactory()
  {
  }
  GameObject *GameObjectFactory::CreatePointLightGo(FurryWolfEngine *engine)
  {
    GameObject *go = engine->CreateGameObject();
    go->AddComponent<PointLightComponent>();
    return go;
  }

}
