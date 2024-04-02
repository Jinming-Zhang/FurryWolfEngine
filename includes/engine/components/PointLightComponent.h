#pragma once
#include "engine/components/LightComponent.h"
namespace WEngine
{
  class PointLightComponent : public LightComponent
  {
    friend class FurryWolfEngine;
    friend class GameObject;

  protected:
    float constant;
    float linear;
    float quadratic;
    static int PointLightIndexer;
    int countId;

  public:
    PointLightComponent();
    ~PointLightComponent();
    virtual void Update(float deltaTime) override;

    void SetConstTerm(float constTerm) { constant = constTerm; }
    void SetLinearTerm(float linearTerm) { linear = linearTerm; }
    void SetQuadraticTerm(float quadraticTerm) { quadratic = quadraticTerm; }
    static void Reset();
  };

}
