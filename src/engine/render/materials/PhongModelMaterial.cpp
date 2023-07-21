
#include "engine/render/Texture.h"
#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/ShaderProgram.h"
#include "engine/components/CameraComponent.h"

namespace WEngine
{
  PhongModelMaterial::PhongModelMaterial()
  {
    objColor = glm::vec3(1.f);
    shininess = 32.f;
  }
  PhongModelMaterial::~PhongModelMaterial() {}

  bool PhongModelMaterial::LoadAlbedoMap(const std::string &path, const TextureLoadConfig &config)
  {
    albedoMap.reset(new Texture());
    return albedoMap->LoadTexture(path, config);
  }
  bool PhongModelMaterial::LoadNormalMap(const std::string &path, const TextureLoadConfig &config)
  {
    normalMap.reset(new Texture());
    return normalMap->LoadTexture(path, config);
  }
  bool PhongModelMaterial::LoadSpecularMap(const std::string &path, const TextureLoadConfig &config)
  {
    specularMap.reset(new Texture());
    return specularMap->LoadTexture(path, config);
  }

  void PhongModelMaterial::Use(GameObject *go)
  {
    albedoMap->Use(GL_TEXTURE0);
    specularMap->Use(GL_TEXTURE2);

    Material::Use(go);
    // set texture unit location
    shaderToUse->SetInt("material.albedoMap", 0);
    shaderToUse->SetInt("material.specularMap", 2);

    shaderToUse->SetFloat("material.shininess", shininess);

    glm::vec3 camPos = CameraComponent::Main()->GetPosition();
    shaderToUse->UseProgram();
    shaderToUse->SetVec3("eyePos", camPos.x, camPos.y, camPos.z);
  }
}
