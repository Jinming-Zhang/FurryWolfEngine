#pragma once
#include "engine/render/Material.h"
namespace WEngine
{
  class DepthVisualizerMaterial : public Material
  {
  private:
    bool useLinear;

  public:
    DepthVisualizerMaterial();
    ~DepthVisualizerMaterial();
    void SetLinear(bool isLinear) { useLinear = isLinear; }
    virtual void Use(class GameObject *gameObject) override;
  };
}
