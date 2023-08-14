#pragma once
#include "engine/math/glm/glm.hpp"
#include "engine/render/Material.h"
namespace WEngine
{
  class GameObject;
  class LightSourceMaterial : public Material
  {
  private:
    glm::vec3 color;

  public:
    LightSourceMaterial(/* args */);
    ~LightSourceMaterial();
    virtual void Use(GameObject *go) override;
    void SetColor(glm::vec3 newColor);
  };
}
