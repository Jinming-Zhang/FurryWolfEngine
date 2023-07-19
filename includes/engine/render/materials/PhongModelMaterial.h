#pragma once
#include "engine/math/glm/glm.hpp"
#include "engine/render/Material.h"
namespace WEngine
{
  class GameObject;
  class PhongModelMaterial : public Material
  {
  private:
    glm::vec3 objColor;
    float shininess;
    float specularStrength;

  public:
    PhongModelMaterial();
    ~PhongModelMaterial();
    void SetObjColor(float r, float g, float b) { objColor = glm::vec3(r, g, b); }
    virtual void Use(GameObject *go) override;
  };

}
