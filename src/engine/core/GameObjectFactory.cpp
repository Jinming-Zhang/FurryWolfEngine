#include "engine/core/FurryWolfEngine.h"
#include "engine/core/ResourceManager.h"
#include "engine/core/GameObject.h"
#include "engine/core/GameObjectFactory.h"

#include "engine/math/glm/glm.hpp"

#include "engine/components/PointLightComponent.h"

#include "engine/components/meshes/IndexedDrawMeshComponent.h"
#include "engine/render/meshes/Mesh.h"

namespace WEngine
{
  GameObjectFactory::~GameObjectFactory() {}

  GameObject *GameObjectFactory::CreatePointLightGo(FurryWolfEngine *engine)
  {
    GameObject *go = engine->CreateGameObject();
    go->AddComponent<PointLightComponent>();
    return go;
  }
  GameObject *GameObjectFactory::CreatePlaneMeshGO(FurryWolfEngine *engine)
  {
    GameObject *go = engine->CreateGameObject();
    IndexedDrawMeshComponent *mesh = go->AddComponent<IndexedDrawMeshComponent>();
    std::vector<Vertex> planeVertices = {
        Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.f, .0f, .0f), glm::vec2(1.f, 1.f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(.0f, 1.f, .0f), glm::vec2(1.f, 0.f)},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(.0f, .0f, 1.f), glm::vec2(0.f, 0.f)},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(.5f, .5f, .5f), glm::vec2(0.f, 1.f)}};
    std::vector<unsigned int> planeIndices = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    mesh->Init(planeVertices, planeIndices);
    mesh->SetMaterial(engine->CreateMaterial<PhongModelMaterial>());
    mesh->GetMaterial()->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Default));

    return go;
  }

  GameObject *GameObjectFactory::CreateCubeMeshGO(FurryWolfEngine *engine)
  {
    GameObject *go = engine->CreateGameObject();
    IndexedDrawMeshComponent *mesh = go->AddComponent<IndexedDrawMeshComponent>();

    std::vector<Vertex> cubeVertices = std::vector<Vertex>{
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},

        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)}};

    std::vector<unsigned int> indices = {
        0, 1, 3, 1, 2, 3, // front
        4, 5, 7, 5, 6, 7, // back
        0, 1, 4, 1, 4, 5, // bottom
        2, 3, 6, 3, 6, 7, // top
        0, 3, 4, 3, 4, 7, // left
        1, 2, 5, 2, 5, 6  // right
    };

    mesh->Init(cubeVertices, indices);
    mesh->SetMaterial(engine->CreateMaterial<PhongModelMaterial>());
    mesh->GetMaterial()->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Default));
    return go;
  }

}
