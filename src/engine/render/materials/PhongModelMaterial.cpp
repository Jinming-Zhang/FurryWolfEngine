#include <memory>
#include <iostream>
#include <vector>
#include "engine/render/Texture.h"
#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/ShaderProgram.h"
#include "engine/components/CameraComponent.h"

namespace WEngine
{
  unsigned int PhongModelMaterial::ALBEDO_MAP_COUNT = 3;
  unsigned int PhongModelMaterial::SPECULAR_MAP_COUNT = 2;
  PhongModelMaterial::PhongModelMaterial()
  {
    albedoMaps = std::vector<std::shared_ptr<Texture>>();
    specularMaps = std::vector<std::shared_ptr<Texture>>();
    objColor = glm::vec3(1.f);
    shininess = 32.f;
  }

  PhongModelMaterial::~PhongModelMaterial() {}

  // bool PhongModelMaterial::AddAlbedoMap(const std::string &path, const TextureLoadConfig &config)
  // {
  //   if (albedoMaps.size() == PhongModelMaterial::ALBEDO_MAP_COUNT)
  //   {
  //     std::cout << "Maximum number of albedo texture reached, adding new albedo map is ignored.\n";
  //     return false;
  //   }
  //   std::unique_ptr albedo = std::make_unique<Texture>();
  //   bool success = albedo->LoadTexture(path, config);
  //   if (!success)
  //   {
  //     return false;
  //   }
  //   albedoMaps.push_back(std::move(albedo));
  //   return true;
  // }

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
  // bool PhongModelMaterial::AddSpecularMap(const std::string &path, const TextureLoadConfig &config)
  // {
  //   if (specularMaps.size() == PhongModelMaterial::SPECULAR_MAP_COUNT)
  //   {
  //     std::cout << "Maximum number of specular texture reached, adding new specular map is ignored.\n";
  //     return false;
  //   }
  //   std::unique_ptr specular = std::make_unique<Texture>();
  //   bool success = specular->LoadTexture(path, config);
  //   if (!success)
  //   {
  //     return false;
  //   }
  //   specularMaps.push_back(std::move(specular));
  //   return true;
  // }

  bool PhongModelMaterial::AddSpecularMap(std::shared_ptr<Texture> texture)
  {
    specularMaps.push_back(texture);
    return true;
  }

  void PhongModelMaterial::Use(GameObject *go)
  {
    Material::Use(go);

    int textureUnitIndex = 0;
    shaderToUse->SetInt("material.albedoMapsCount", albedoMaps.size());
    for (size_t i{0}; i < albedoMaps.size(); ++i)
    {
      albedoMaps[i]->Use(GL_TEXTURE0 + textureUnitIndex);
      std::string prefix{"material.albedoMap"};
      prefix.append(std::to_string(i));
      shaderToUse->SetInt(prefix.c_str(), textureUnitIndex);
      ++textureUnitIndex;
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
