#pragma once
#include "engine/core/FurryWolfEngine.h"
#include "engine/core/GameObject.h"

#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/LightComponent.h"
#include "engine/components/DirectionalLightComponent.h"

#include "engine/render/Mesh.h"
#include "engine/render/VerticesMesh.h"
#include "engine/render/LightSourceShaderProgram.h"

#include "engine/render/Material.h"
#include "engine/render/materials/LightSourceMaterial.h"
#include "engine/render/materials/PhongModelMaterial.h"

#include "game/FancyLight.h"
namespace WEngine
{
  class SceneMaker
  {
  private:
    static float cubeVertices[];

  public:
    SceneMaker() {}
    static void MakeLotsCubeScene(FurryWolfEngine *engine);
    static void MakeLightScene(FurryWolfEngine *engine);
    ~SceneMaker() {}
  };

  void SceneMaker::MakeLotsCubeScene(FurryWolfEngine *engine)
  {
    float sampleMeshVertices[] = {
        // positions        // colors       // texture coordinates
        0.5f, 0.5f, 0.0f, 1.f, .0f, .0f, 1.f, 1.f,   // top right
        0.5f, -0.5f, 0.0f, .0f, 1.f, .0f, 1.f, 0.f,  // bottom right
        -0.5f, -0.5f, 0.0f, .0f, .0f, 1.f, 0.f, 0.f, // bottom left
        -0.5f, 0.5f, 0.0f, .5f, .5f, .5f, 0.f, 1.f   // top left
    };
    unsigned int sampleMeshIndices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    engine->mesh1 = new Mesh();
    engine->mesh1->Init(sampleMeshVertices, 32, sampleMeshIndices, 6);
    engine->mesh2 = new Mesh();
    engine->mesh2->Init(sampleMeshVertices, 32, sampleMeshIndices, 6);

    engine->mesh1->SetShader(engine->phongShader);
    engine->mesh2->SetShader(engine->phongShader);

    glm::vec3 cubePositions[] = {
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

    for (size_t i{0}; i < 10; ++i)
    {
      GameObject *go = engine->CreateGameObject();
      VerticesMesh *vMesh = go->AddComponent<VerticesMesh>();
      vMesh->Init(SceneMaker::cubeVertices, 180);
      vMesh->SetShader(engine->phongShader);
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
    engine->camera = CameraComponent::Main();
    engine->camera->SetPosition(glm::vec3(.0f, .0f, 3.f));
    // light source
    GameObject *lightGo = engine->CreateGameObject();
    glm::mat4 model = glm::mat4{1.f};
    model = glm::translate(model, glm::vec3(1.2f, 1.f, 2.f));
    model = glm::scale(model, glm::vec3(.2f));
    lightGo->GetComponent<TransformComponent *>()->SetModel(model);
    lightGo->GetComponent<TransformComponent *>()->SetPosition(1.2f, 1.f, 2.f);
    // light source mesh
    VerticesMesh *lightMesh = lightGo->AddComponent<VerticesMesh>();
    lightMesh->Init(SceneMaker::cubeVertices, 288);
    Material *lightGoMat = engine->CreateMaterial<LightSourceMaterial>();
    lightGoMat->SetShader(engine->lightSourceSp);
    lightMesh->SetMaterial(lightGoMat);
    // light component
    DirectionalLightComponent *light = lightGo->AddComponent<DirectionalLightComponent>();
    light->SetShader(engine->phongShader);
    light->SetColor(glm::vec3(1.f, 1.f, 1.f));

    // toy
    GameObject *toy = engine->CreateGameObject();
    VerticesMesh *vMesh = toy->AddComponent<VerticesMesh>();
    toy->GetComponent<TransformComponent *>()->SetPosition(.0f, .0f, .0f);
    vMesh->Init(SceneMaker::cubeVertices, 288);
    PhongModelMaterial *phongMat = engine->CreateMaterial<PhongModelMaterial>();
    phongMat->SetObjColor(1.f, .5f, .31f);
    phongMat->SetShader(engine->phongShader);
    vMesh->SetMaterial(phongMat);

    WEngine::TextureLoadConfig texLoadConfig{};
    texLoadConfig.internalFormat = GL_RGBA;
    std::string albedoPath{"assets/images/textures/container2.png"};
    std::string specularPath{"assets/images/textures/container2_specular.png"};
    phongMat->LoadAlbedoMap(albedoPath, texLoadConfig);
    texLoadConfig.textureUnit = GL_TEXTURE1;
    phongMat->LoadSpecularMap(specularPath, texLoadConfig);
  }

  float SceneMaker::cubeVertices[] = {
      // position            tex coord   normal
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
}
