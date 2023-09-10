#include <memory>
#include <iostream>
#include <vector>
#include "engine/render/Texture.h"
#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/ShaderProgram.h"
#include "engine/components/CameraComponent.h"
#include "engine/core/ResourceManager.h"

namespace WEngine
{
  unsigned int PhongModelMaterial::ALBEDO_MAP_COUNT = 3;
  unsigned int PhongModelMaterial::SPECULAR_MAP_COUNT = 2;
  PhongModelMaterial::PhongModelMaterial()
  {
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong);
    albedoMaps = std::vector<std::shared_ptr<Texture>>();
    specularMaps = std::vector<std::shared_ptr<Texture>>();
    baseColor = glm::vec3(1.f);
    shininess = 32.f;
  }

  PhongModelMaterial::~PhongModelMaterial() {}

  bool PhongModelMaterial::AddAlbedoMap(std::shared_ptr<Texture> texture)
  {
    albedoMaps.push_back(texture);
    return true;
  }

  bool PhongModelMaterial::LoadNormalMap(const std::string &path, const TextureLoadConfig &config)
  {
    normalMap.reset(new Texture());
    return normalMap->LoadTexture(path, config);
  }

  bool PhongModelMaterial::AddSpecularMap(std::shared_ptr<Texture> texture)
  {
    specularMaps.push_back(texture);
    return true;
  }

  void PhongModelMaterial::Use(GameObject *go)
  {
    Material::Use(go);

    shaderToUse->SetVec3("baseColor", baseColor.r, baseColor.g, baseColor.b);

    int textureUnitIndex = 0;
    shaderToUse->SetInt("material.albedoMapsCount", albedoMaps.size());
    if (albedoMaps.size() == 0)
    {
      std::shared_ptr<Texture> texture = ResourceManager::Instance()->LoadTexture("./assets/defaults/defaultTexture.png");
      texture->Use(GL_TEXTURE0 + textureUnitIndex);
      std::string prefix{"material.albedoMap"};
      prefix.append(std::to_string(0));
      shaderToUse->SetInt(prefix.c_str(), textureUnitIndex);
      ++textureUnitIndex;
    }
    else
    {
      for (size_t i{0}; i < albedoMaps.size(); ++i)
      {
        albedoMaps[i]->Use(GL_TEXTURE0 + textureUnitIndex);
        std::string prefix{"material.albedoMap"};
        prefix.append(std::to_string(i));
        shaderToUse->SetInt(prefix.c_str(), textureUnitIndex);
        ++textureUnitIndex;
      }
    }
    shaderToUse->SetInt("material.specularMapsCount", specularMaps.size());
    for (size_t i{0}; i < specularMaps.size(); ++i)
    {
      specularMaps[i]->Use(GL_TEXTURE0 + textureUnitIndex);
      std::string prefix{"material.specularMap"};
      prefix.append(std::to_string(i));
      shaderToUse->SetInt(prefix.c_str(), textureUnitIndex);
      ++textureUnitIndex;
    }

    shaderToUse->SetFloat("material.shininess", shininess);

    glm::vec3 camPos = CameraComponent::Main()->GetPosition();
    shaderToUse->UseProgram();
    shaderToUse->SetVec3("eyePos", camPos.x, camPos.y, camPos.z);
  }
}
