#include "engine/core/Scene.h"

#include "engine/core/FurryWolfEngine.h"
#include "engine/core/GameObject.h"
#include "engine/core/GameObjectFactory.h"
#include "engine/components/CameraComponent.h"
namespace WEngine
{

  Scene::Scene(FurryWolfEngine *engine)
  {
    this->engine = engine;
    CreateDefaultScene();
  }
  Scene::~Scene() { DestroyScene(); }

  void Scene::CreateDefaultScene()
  {
    AddGameObject(GameObjectFactory::CreateDirectionalLightGo(this->engine));
    AddGameObject(GameObjectFactory::CreateCamera(this->engine));
  }

  void Scene::AddGameObject(GameObject *gameobject)
  {
    gameobjects.push_back(gameobject);
  }
  void Scene::Load()
  {
    for (auto go : gameobjects)
    {
      go->Awake();
    }
  }
  void Scene::Start()
  {
    for (auto go : gameobjects)
    {
      go->Start();
    }
  }
  void Scene::Refresh(float deltaTime)
  {
    for (auto &go : gameobjects)
    {
      go->Update(deltaTime);
    }
    for (auto &go : gameobjects)
    {
      go->LateUpdate(deltaTime);
    }

    // opaque pass
    for (auto &go : gameobjects)
    {
      go->Render(false);
    }
    // transparent pass
    for (auto &go : gameobjects)
    {
      go->Render(true);
    }
  }

  void Scene::DestroyScene()
  {
    for (auto go : this->gameobjects)
    {
      go->Destroy();
      delete go;
    }
    gameobjects.clear();
  }
}
