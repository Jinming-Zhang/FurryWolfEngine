#include "engine/core/Scene.h"
#include <map>

#include "engine//math/glm/glm.hpp"
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
    loaded = false;
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

  int Scene::GetPointLightsCount()
  {
    return pointLightsCount;
  }

  int Scene::GetSpotLightsCount()
  {
    return spointLightsCount;
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
    GameObject *newMainCamGO = FindObjectOfType<CameraComponent *>();
    if (newMainCamGO != nullptr)
    {
      CameraComponent *newMainCamCmp = newMainCamGO->GetComponent<CameraComponent *>();
      CameraComponent::SetMainCamera(newMainCamCmp);
    }
  }
  void Scene::Refresh(float deltaTime)
  {
    const ShaderProgram &phongShader = ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong);
    phongShader.UseProgram();
    int pLightsCount = GetPointLightsCount();
    int spLightsCount = GetSpotLightsCount();
    phongShader.SetInt("pLightsCount", pLightsCount);
    phongShader.SetInt("spLightsCount", spLightsCount);
    for (auto &go : gameobjects)
    {
      go->Update(deltaTime);
    }
    for (auto &go : gameobjects)
    {
      go->LateUpdate(deltaTime);
    }

    GameObject *newMainCamGO = FindObjectOfType<CameraComponent *>();
    CameraComponent *mainCam = newMainCamGO->GetComponent<CameraComponent *>();
    glm::vec3 camPos = mainCam->GetPosition();
    // std::cout << "Camera Position:" << camPos.x << " ," << camPos.y << " ," << camPos.z << "\n";

    std::map<float, GameObject *> sorted = std::map<float, GameObject *>();
    for (auto &go : gameobjects)
    {
      glm::vec3 objPos = go->GetComponent<TransformComponent *>()->GetLocalPosition();
      float distance = glm::length(objPos - camPos);
      sorted[distance] = go;
    }

    // opaque pass
    for (auto &go : gameobjects)
    {
      go->Render(false);
    }
    // transparent pass
    for (auto it{sorted.rbegin()}; it != sorted.rend(); ++it)
    {
      // float dst = it->first;
      it->second->Render(true);
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
