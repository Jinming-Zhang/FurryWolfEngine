#include "engine/render/materials/LightSourceMaterial.h"
#include "engine/render/ShaderProgram.h"
#include "engine/core/ResourceManager.h"
namespace WEngine
{
  LightSourceMaterial::LightSourceMaterial()
  {
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::LightSource);
  }
  LightSourceMaterial::~LightSourceMaterial() {}

  void LightSourceMaterial::Use(GameObject *go)
  {
    Material::Use(go);
    shaderToUse->SetVec3("lightSourceColor", color.r, color.g, color.b);
  }
  void LightSourceMaterial::SetColor(glm::vec3 newColor)
  {
    color = newColor;
  }
}
