#pragma once
#include "engine/components/LightComponent.h"
#include "engine/math/glm/glm.hpp"

namespace WEngine
{
  class DirectionalLightComponent : public LightComponent
  {
  private:
    glm::vec3 direction;

  public:
    DirectionalLightComponent(/* args */);
    virtual void Update(float deltaTime)override;
    ~DirectionalLightComponent();
  };

}
