#pragma once
#include "engine/math/glm/glm.hpp"
#include "engine/components/PointLightComponent.h"
namespace WEngine
{
  class SpotLightComponent : public PointLightComponent
  {
    friend class FurryWolfEngine;
    friend class GameObject;
  private:
    glm::vec3 direction;
    float innerCutOffAngle;
    float outterCutOffAngle;
    static int SpotLightIndexer;
    int countId;

  public:
    SpotLightComponent();
    virtual void Update(float deltaTime) override;
    ~SpotLightComponent();
  };

}
