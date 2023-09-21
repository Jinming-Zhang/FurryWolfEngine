#include "engine/core/ResourceManager.h"
#include "engine/render/materials/SimpleUnlitMaterial.h"
#include "engine/render/ShaderProgram.h"
#include "engine/render/Texture.h"
namespace WEngine
{
  SimpleUnlitMaterial::SimpleUnlitMaterial()
  {
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::SimpleUnlit);
    albedoMaps = std::vector<std::shared_ptr<Texture>>();
    baseColor = glm::vec3(1.f);
  }

  SimpleUnlitMaterial::~SimpleUnlitMaterial() {}

  bool SimpleUnlitMaterial::AddAlbedoMap(std::shared_ptr<Texture> texture)
  {
    albedoMaps.push_back(texture);
    return true;
  }

  void SimpleUnlitMaterial::Use(GameObject *go)
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
  }
}
