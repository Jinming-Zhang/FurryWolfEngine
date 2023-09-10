#include "engine/render/materials/DepthVisualizerMaterial.h"
#include "engine/core/ResourceManager.h"
namespace WEngine
{
  DepthVisualizerMaterial::DepthVisualizerMaterial()
  {
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::DepthVisualizer);
    useLinear = true;
  }

  DepthVisualizerMaterial::~DepthVisualizerMaterial()
  {
  }
  void DepthVisualizerMaterial::Use(GameObject *gameObject)
  {
    Material::Use(gameObject);
    if (useLinear)
    {
      shaderToUse->SetInt("linear", 1);
    }
    else
    {
      shaderToUse->SetInt("linear", 0);
    }
  }
}
