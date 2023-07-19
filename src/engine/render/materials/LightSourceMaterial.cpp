#include "engine/render/materials/LightSourceMaterial.h"
#include "engine/render/ShaderProgram.h"
namespace WEngine
{
  LightSourceMaterial::LightSourceMaterial() {}
  LightSourceMaterial::~LightSourceMaterial() {}

  void LightSourceMaterial::Use(GameObject *go)
  {
    Material::Use(go);
    shaderToUse->SetVec3("lightSourceColor", .3f, .3f, 1.f);
  }
}
