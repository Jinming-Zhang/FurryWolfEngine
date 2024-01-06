#include "engine/render/materials/CubemapSkyboxMaterial.h"
#include "engine/core/ResourceManager.h"
#include "engine/components/CameraComponent.h"
namespace WEngine
{
  CubemapSkyboxMaterial::CubemapSkyboxMaterial()
  {
    cubeMapTexture = ResourceManager::Instance()->LoadTexture<CubeMapTexture>("defaultSkyboxCubemap");
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::CubemapSkybox);
  }

  CubemapSkyboxMaterial::~CubemapSkyboxMaterial()
  {
  }

  void CubemapSkyboxMaterial::AssignCubemapTexture(std::shared_ptr<CubeMapTexture> texture)
  {
    cubeMapTexture = texture;
  }

  void CubemapSkyboxMaterial::Use(GameObject *go)
  {
    CameraComponent *main{CameraComponent::Main()};
    if (main == nullptr)
    {
      return;
    }
    shaderToUse->UseProgram();
    shaderToUse->SetMat4("projection", main->GetProjectionMatrix());
    shaderToUse->SetMat4("view", glm::mat4{glm::mat3{main->GetViewMatrix()}});
    cubeMapTexture->Use(GL_TEXTURE0);
    shaderToUse->SetInt("cubemap", 0);
  }
}
