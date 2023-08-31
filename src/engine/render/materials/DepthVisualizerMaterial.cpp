#include "engine/render/materials/DepthVisualizerMaterial.h"
#include "engine/core/ResourceManager.h"
namespace WEngine
{
  DepthVisualizerMaterial::DepthVisualizerMaterial()
  {
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::DepthVisualizer);
  }

  DepthVisualizerMaterial::~DepthVisualizerMaterial()
  {
  }
}
