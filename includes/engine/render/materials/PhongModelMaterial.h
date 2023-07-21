#pragma once
#include <memory>
#include "engine/math/glm/glm.hpp"
#include "engine/render/Texture.h"
#include "engine/render/Material.h"
namespace WEngine
{
  class GameObject;
  class PhongModelMaterial : public Material
  {
  private:
    glm::vec3 objColor;
    float shininess;
    std::unique_ptr<Texture> albedoMap;
    std::unique_ptr<Texture> normalMap;
    std::unique_ptr<Texture> specularMap;

  public:
    PhongModelMaterial();
    bool LoadAlbedoMap(const std::string &path, const TextureLoadConfig &config);
    bool LoadNormalMap(const std::string &path, const TextureLoadConfig &config);
    bool LoadSpecularMap(const std::string &path, const TextureLoadConfig &config);
    ~PhongModelMaterial();
    void SetObjColor(float r, float g, float b) { objColor = glm::vec3(r, g, b); }
    virtual void Use(GameObject *go) override;
  };

}
