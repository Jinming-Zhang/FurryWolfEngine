#pragma once
#include "engine/components/Component.h"
#include "engine/components/LightComponent.h"

class FancyLight : public WEngine::Component
{
private:
  /* data */
public:
  FancyLight(/* args */);
  virtual void Update(float deltaTime) override;
  ~FancyLight();
};
