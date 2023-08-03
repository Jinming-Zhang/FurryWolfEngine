#pragma once
#include <memory>
#include <vector>
#include "engine/math/glm/glm.hpp"
#include "engine/render/Texture.h"
#include "engine/render/Material.h"
namespace WEngine
{
  class GameObject;
  class PhongModelMaterial : public Material
  {
  private:
    static unsigned int ALBEDO_MAP_COUNT;
    static unsigned int SPECULAR_MAP_COUNT;
    glm::vec3 objColor;
    float shininess;
    std::unique_ptr<Texture> normalMap;

    std::vector<std::shared_ptr<Texture>> albedoMaps;
    std::vector<std::shared_ptr<Texture>> specularMaps;

  public:
    PhongModelMaterial();
    // bool AddAlbedoMap(const std::string &path, const TextureLoadConfig &config);
    bool AddAlbedoMap(std::shared_ptr<Texture> texture);
    bool LoadNormalMap(const std::string &path, const TextureLoadConfig &config);
    // bool AddSpecularMap(const std::string &path, const TextureLoadConfig &config);
    bool AddSpecularMap(std::shared_ptr<Texture> texture);
    ~PhongModelMaterial();
    void SetObjColor(float r, float g, float b) { objColor = glm::vec3(r, g, b); }
    virtual void Use(GameObject *go) override;
  };

}
