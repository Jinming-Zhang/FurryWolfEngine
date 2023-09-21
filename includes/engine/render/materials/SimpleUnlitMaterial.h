#pragma once
#include <vector>
#include <memory>

#include "engine/math/glm/glm.hpp"
#include "engine/render/Material.h"
namespace WEngine
{
  class Texture;
  class GameObject;
  class SimpleUnlitMaterial : public Material
  {
  private:
    std::vector<std::shared_ptr<Texture>> albedoMaps;
    glm::vec3 baseColor;

  public:
    SimpleUnlitMaterial();
    ~SimpleUnlitMaterial();
    bool AddAlbedoMap(std::shared_ptr<Texture> texture);
    void SetBaseColor(float r, float g, float b) { baseColor = glm::vec3(r, g, b); }
    virtual void Use(GameObject *go) override;
  };

}
