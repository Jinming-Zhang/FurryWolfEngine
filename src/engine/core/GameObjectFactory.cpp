#include "engine/core/FurryWolfEngine.h"
#include "engine/core/ResourceManager.h"
#include "engine/core/GameObject.h"
#include "engine/core/GameObjectFactory.h"

#include "engine/math/glm/glm.hpp"

#include "engine/components/PointLightComponent.h"

#include "engine/components/meshes/IndexedDrawMeshComponent.h"
#include "engine/components/meshes/VerticesDrawMeshComponent.h"
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
    // GameObject *go = engine->CreateGameObject();
    // IndexedDrawMeshComponent *mesh = go->AddComponent<IndexedDrawMeshComponent>();
    // std::vector<Vertex> planeVertices = {
    //     Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.f, .0f, .0f), glm::vec2(1.f, 1.f)},
    //     Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(.0f, 1.f, .0f), glm::vec2(1.f, 0.f)},
    //     Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(.0f, .0f, 1.f), glm::vec2(0.f, 0.f)},
    //     Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(.5f, .5f, .5f), glm::vec2(0.f, 1.f)}};
    // std::vector<unsigned int> planeIndices = {
    //     // note that we start from 0!
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };
    // mesh->Init(planeVertices, planeIndices);
    // mesh->SetMaterial(engine->CreateMaterial<PhongModelMaterial>());
    // mesh->GetMaterial()->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Default));

    GameObject *go = engine->CreateGameObject();
    VerticesDrawMeshComponent *vmeshcmp = go->AddComponent<VerticesDrawMeshComponent>();
    std::vector<Vertex> planeVertices = {
        Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.f, .0f, .0f), glm::vec2(1.f, 1.f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(.0f, 1.f, .0f), glm::vec2(1.f, 0.f)},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(.0f, .0f, 1.f), glm::vec2(0.f, 0.f)},

        Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.f, .0f, .0f), glm::vec2(1.f, 1.f)},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(.5f, .5f, .5f), glm::vec2(0.f, 1.f)},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(.0f, .0f, 1.f), glm::vec2(0.f, 0.f)},
    };
    vmeshcmp->Init(planeVertices);
    PhongModelMaterial *mat = engine->CreateMaterial<PhongModelMaterial>();
    mat->SetBaseColor(.0f, 100.f, 100.f);
    mat->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong));
    vmeshcmp->SetMaterial(mat);
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

  GameObject *GameObjectFactory::CreateSphereMeshGO(FurryWolfEngine *engine, int segments, int rings)
  {
    GameObject *go = engine->CreateGameObject();
    VerticesDrawMeshComponent *mesh = go->AddComponent<VerticesDrawMeshComponent>();

    float pi{3.1415926f};
    std::vector<Vertex> vertices{};
    float deltaTheta{2.f * pi / segments};
    float deltaPhi = pi / rings;

    float theta0{0.f};     // segment angle
    float phi0{-pi / 2.f}; // ring angle
    for (int phiInd{0}; phiInd < rings; ++phiInd)
    {
      int nextPhi = (phiInd + 1) % rings;
      float phiSouth = phi0 + deltaPhi * phiInd;
      float phiEast = phi0 + deltaPhi * nextPhi;

      for (int thetaInd = 0; thetaInd < segments; ++thetaInd)
      {
        int nextThetaInd = (thetaInd + 1) % segments;
        float thetaSouth = theta0 * thetaInd * deltaTheta;
        float thetaEast = theta0 * nextThetaInd * deltaTheta;

        glm::vec3 pSS = PolarToPoint(thetaSouth, phiSouth, 1.f);
        glm::vec3 pSE = PolarToPoint(thetaSouth, phiEast, 1.f);
        glm::vec3 pES = PolarToPoint(thetaEast, phiEast, 1.f);
        glm::vec3 pEE = PolarToPoint(thetaEast, phiEast, 1.f);

        if (phiInd == 0)
        {
          vertices.push_back(Vertex{pSS, glm::normalize(pSS), glm::vec2{.0f}});
          vertices.push_back(Vertex{pSE, glm::normalize(pSE), glm::vec2{.0f}});
          vertices.push_back(Vertex{pEE, glm::normalize(pEE), glm::vec2{.0f}});
        }
        else if (nextPhi == rings)
        {
          vertices.push_back(Vertex{pEE, glm::normalize(pEE), glm::vec2{.0f}});
          vertices.push_back(Vertex{pES, glm::normalize(pES), glm::vec2{.0f}});
          vertices.push_back(Vertex{pSS, glm::normalize(pSS), glm::vec2{.0f}});
        }
        else
        {
          vertices.push_back(Vertex{pSS, glm::normalize(pSS), glm::vec2{.0f}});
          vertices.push_back(Vertex{pSE, glm::normalize(pSE), glm::vec2{.0f}});
          vertices.push_back(Vertex{pEE, glm::normalize(pEE), glm::vec2{.0f}});

          vertices.push_back(Vertex{pEE, glm::normalize(pEE), glm::vec2{.0f}});
          vertices.push_back(Vertex{pES, glm::normalize(pES), glm::vec2{.0f}});
          vertices.push_back(Vertex{pSS, glm::normalize(pSS), glm::vec2{.0f}});
        }
      }
    }

    mesh->Init(vertices);
    mesh->SetMaterial(engine->CreateMaterial<PhongModelMaterial>());
    mesh->GetMaterial()->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Default));
    return go;
  }

  glm::vec3 GameObjectFactory::PolarToPoint(float theta, float phi, float radius)
  {
    float r = radius * glm::cos(phi);
    float x = r * glm::cos(theta);
    float y = r * glm::sin(theta);
    float z = radius * glm::sin(phi);
    return glm::vec3{x, y, z};
  }

}
