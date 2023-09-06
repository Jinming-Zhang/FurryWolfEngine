#pragma once

#include "engine/core/FurryWolfEngine.h"
#include "engine/core/ResourceManager.h"
#include "engine/core/GameObject.h"
#include "engine/core/GameObjectFactory.h"

#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/LightComponent.h"
#include "engine/components/DirectionalLightComponent.h"
#include "engine/components/PointLightComponent.h"
#include "engine/components/SpotLightComponent.h"

#include "engine/render/meshes/Mesh.h"
#include "engine/components/meshes/MeshComponent.h"
#include "engine/components/meshes/IndexedDrawMeshComponent.h"
#include "engine/components/meshes/VerticesDrawMeshComponent.h"
#include "engine/components/meshes/ModelComponent.h"

#include "engine/render/LightSourceShaderProgram.h"

#include "engine/render/Material.h"
#include "engine/render/materials/LightSourceMaterial.h"
#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/materials/DepthVisualizerMaterial.h"
#include "engine/render/materials/StencilOutlineMaterial.h"

#include "game/FancyLight.h"
namespace WEngine
{
  class SceneMaker
  {
  private:
    static std::vector<Vertex> cubeVertices;
    static glm::vec3 cubePositions[];

  public:
    SceneMaker() {}
    static void MakeLotsCubeScene(FurryWolfEngine *engine);
    static void MakeLightScene(FurryWolfEngine *engine);
    static void MakeDepthVisualizationScene(FurryWolfEngine *engine);
    ~SceneMaker() {}
  };

  void SceneMaker::MakeLotsCubeScene(FurryWolfEngine *engine)
  {
    std::vector<Vertex> sampleMeshVertices = {
        Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.f, .0f, .0f), glm::vec2(1.f, 1.f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(.0f, 1.f, .0f), glm::vec2(1.f, 0.f)},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(.0f, .0f, 1.f), glm::vec2(0.f, 0.f)},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(.5f, .5f, .5f), glm::vec2(0.f, 1.f)}};
    std::vector<unsigned int> sampleMeshIndices = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GameObject *go = engine->CreateGameObject();
    IndexedDrawMeshComponent *indDrawCmp = go->AddComponent<IndexedDrawMeshComponent>();
    indDrawCmp->Init(sampleMeshVertices, sampleMeshIndices);

    for (size_t i{0}; i < 10; ++i)
    {
      GameObject *go = engine->CreateGameObject();
      VerticesDrawMeshComponent *vMeshCmp = go->AddComponent<VerticesDrawMeshComponent>();
      vMeshCmp->Init(SceneMaker::cubeVertices);
      TransformComponent *transform = go->GetComponent<TransformComponent *>();
      glm::vec3 pos = cubePositions[i];
      transform->SetPosition(pos);
      glm::mat4 &rot = transform->GetRotationMatrix();
      rot = glm::rotate(rot, glm::radians(i * 20.f), glm::vec3(1.f, .3f, .5f));
    }

    glm::mat4 model{1.f};
    model = glm::rotate(model, glm::radians(-55.f), glm::vec3{1.f, .0f, .0f});

    glm::mat4 model2{1.f};
    model2 = glm::scale(model2, glm::vec3(.5f, .5f, .5f));
    model2 = glm::rotate(model2, glm::radians(-55.f), glm::vec3{1.f, .0f, .0f});
    model2 = glm::translate(model2, glm::vec3{1.5f, 0.f, 0.f});

    engine->camera = CameraComponent::Main();
    engine->camera->SetPosition(glm::vec3(.0f, .0f, 3.f));
  }

  void SceneMaker::MakeLightScene(FurryWolfEngine *engine)
  {
    ShaderProgram *phongShader = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong);
    ShaderProgram *lightSourceSp = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::LightSource);

    GameObject *cameraGo = engine->CreateGameObject();
    engine->camera = CameraComponent::Main();
    engine->camera->gameObject = cameraGo;
    engine->camera->SetPosition(glm::vec3(.0f, .0f, 3.f));

    SpotLightComponent *flashLight = engine->camera->gameObject->AddComponent<SpotLightComponent>();
    flashLight->SetShader(phongShader);
    flashLight->SetColor(glm::vec3(1.f));

    // directional light source
    GameObject *lightGo = engine->CreateGameObject();
    glm::mat4 model = glm::mat4{1.f};
    model = glm::translate(model, glm::vec3(1.2f, 1.f, 2.f));
    model = glm::scale(model, glm::vec3(.2f));
    lightGo->GetComponent<TransformComponent *>()->SetModel(model);
    lightGo->GetComponent<TransformComponent *>()->SetPosition(1.2f, 1.f, 2.f);
    // light source mesh
    VerticesDrawMeshComponent *lightMesh = lightGo->AddComponent<VerticesDrawMeshComponent>();
    lightMesh->Init(SceneMaker::cubeVertices);
    LightSourceMaterial *lightGoMat = engine->CreateMaterial<LightSourceMaterial>();
    lightGoMat->SetShader(lightSourceSp);
    lightMesh->SetMaterial(lightGoMat);

    // light component
    DirectionalLightComponent *dLight = lightGo->AddComponent<DirectionalLightComponent>();
    dLight->SetShader(phongShader);
    glm::vec3 dLightColor = glm::vec3(1.f, 1.f, 1.f);
    dLight->SetColor(dLightColor);
    lightGoMat->SetColor(dLightColor);

    // point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, -8.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)};

    for (int i = 0; i < 4; ++i)
    {
      GameObject *pLightGO = GameObjectFactory::CreatePointLightGo(engine);
      // mesh
      VerticesDrawMeshComponent *lightMesh = pLightGO->AddComponent<VerticesDrawMeshComponent>();
      lightMesh->Init(SceneMaker::cubeVertices);
      LightSourceMaterial *lightGoMat = engine->CreateMaterial<LightSourceMaterial>();
      lightGoMat->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::LightSource));
      lightMesh->SetMaterial(lightGoMat);

      PointLightComponent *pLightCmp = pLightGO->GetComponent<PointLightComponent *>();
      pLightCmp->SetShader(phongShader);
      glm::vec3 pLightColor = glm::vec3(i * .25f);
      pLightCmp->SetColor(pLightColor);
      lightGoMat->SetColor(pLightColor);
      glm::mat4 model{1.0f};
      model = glm::translate(model, pointLightPositions[i]);
      pLightCmp->transform->SetModel(model);
    }

    // toy
    // material
    PhongModelMaterial *phongMat = engine->CreateMaterial<PhongModelMaterial>();
    phongMat->SetObjColor(1.f, .5f, .31f);
    phongMat->SetObjColor(1.f, 1.f, 1.f);
    phongMat->SetShader(phongShader);
    std::string albedoPath{"assets/images/textures/container2.png"};
    std::string specularPath{"assets/images/textures/container2_specular.png"};
    auto albedoMap1 = ResourceManager::Instance()->LoadTexture(albedoPath);
    auto specularMap1 = ResourceManager::Instance()->LoadTexture(specularPath);
    phongMat->AddAlbedoMap(albedoMap1);
    phongMat->AddSpecularMap(specularMap1);

    for (size_t i{0}; i < 10; ++i)
    {
      GameObject *toy = engine->CreateGameObject("Toy No " + std::to_string(i));
      VerticesDrawMeshComponent *vMesh = toy->AddComponent<VerticesDrawMeshComponent>();
      vMesh->Init(SceneMaker::cubeVertices);
      vMesh->SetMaterial(phongMat);
      TransformComponent *transform = toy->GetComponent<TransformComponent *>();
      glm::vec3 pos = cubePositions[i];
      glm::mat4 model{1.f};
      model = glm::translate(model, pos);
      model = glm::rotate(model, glm::radians(i * 20.f), glm::vec3(1.f, .3f, .5f));
      transform->SetModel(model);
    }

    // import model
    GameObject *backpackModel = engine->CreateGameObject("Backpack");
    ModelComponent *modelCmp = backpackModel->AddComponent<ModelComponent>();
    modelCmp->Init("./assets/models/backpack/backpack.obj");
    // modelCmp->Init("./assets/models/obj/Wolf_obj.obj");
    TransformComponent *backpackTf = backpackModel->GetComponent<TransformComponent *>();
    glm::mat4 backpackModelMat{1.f};
    backpackModelMat = glm::translate(backpackModelMat, glm::vec3(0.f, 0.f, -1.f));
    backpackModelMat = glm::scale(backpackModelMat, glm::vec3(0.5f));
    backpackTf->SetModel(backpackModelMat);

    // GameObject *indDrawSample = engine->CreateGameObject("IndexedDrawSample");
    // IndexedDrawMeshComponent *indDrawSampleMeshCmp = indDrawSample->AddComponent<IndexedDrawMeshComponent>();
    // indDrawSampleMeshCmp->Init(cubeVertices, std::vector<unsigned int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36});
    // indDrawSampleMeshCmp->SetPhongMaterial(phongMat);
  }
  void SceneMaker::MakeDepthVisualizationScene(FurryWolfEngine *engine)
  {
    GameObject *plane = GameObjectFactory::CreatePlaneMeshGO(engine);
    GameObject *cube1 = GameObjectFactory::CreateCubeMeshGO(engine);
    GameObject *cube2 = GameObjectFactory::CreateCubeMeshGO(engine);

    glm::mat4 model{1.f};
    model = glm::translate(model, glm::vec3(-1.f, 0.f, -1.f));
    cube1->GetComponent<TransformComponent *>()->SetModel(model);

    model = glm::mat4{1.f};
    model = glm::translate(model, glm::vec3(2.f, 0.f, 0.f));
    cube2->GetComponent<TransformComponent *>()->SetModel(model);

    model = glm::mat4{1.f};
    model = glm::translate(model, glm::vec3{0.0f, -2.f, .0f});
    model = glm::rotate(model, glm::radians(90.f), glm::vec3{1.f, .0f, .0f});
    model = glm::scale(model, glm::vec3{10.f});
    plane->GetComponent<TransformComponent *>()->SetModel(model);

    StencilOutlineMaterial *outlineMat = engine->CreateMaterial<StencilOutlineMaterial>();
    cube1->GetComponent<MeshComponent *>()
        ->SetMaterial(outlineMat);

    cube2->GetComponent<MeshComponent *>()->SetMaterial(engine->CreateMaterial<DepthVisualizerMaterial>());

    engine->camera = CameraComponent::Main();
    engine->camera->SetPosition(glm::vec3(.0f, .0f, 3.f));
  }

  std::vector<Vertex> SceneMaker::cubeVertices = std::vector<Vertex>{
      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},

      Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

      Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
      Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

      Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

      Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
      Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
      Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}};

  glm::vec3 SceneMaker::cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f)};
}
