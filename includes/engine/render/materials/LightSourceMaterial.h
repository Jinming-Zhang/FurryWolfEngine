#pragma once
#include "engine/render/Material.h"
namespace WEngine
{
  class GameObject;
  class LightSourceMaterial : public Material
  {
  private:
    /* data */
  public:
    LightSourceMaterial(/* args */);
    ~LightSourceMaterial();
    virtual void Use(GameObject *go) override;
  };
}
