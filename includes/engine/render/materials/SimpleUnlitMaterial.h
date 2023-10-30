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
    bool opaque;
    float transparency;

  public:
    SimpleUnlitMaterial();
    ~SimpleUnlitMaterial();
    virtual void Use(GameObject *go) override;
    bool AddAlbedoMap(std::shared_ptr<Texture> texture);
    void SetBaseColor(float r, float g, float b) { baseColor = glm::vec3(r, g, b); }

    void SetOpaque(bool isOpaque) { this->opaque = isOpaque; }
    void SetTransparency(float transparency)
    {
      this->transparency = transparency;
    }
  };

}
