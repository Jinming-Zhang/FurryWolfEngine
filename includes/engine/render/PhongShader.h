#pragma once
#include <vector>
#include <string>

#include "engine/math/glm/glm.hpp"

#include "engine/render/ShaderProgram.h"
#include "engine/render/Texture.h"
namespace WEngine
{
  class PhongShader : public ShaderProgram
  {
  private:
    std::vector<Texture *> albedoTextures;
    Texture *normalTexture;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

  public:
    PhongShader();
    ~PhongShader();

    bool AddAlbedoTexture(std::string texturePath, TextureLoadConfig &config);
    bool SetNormalTexture(std::string texturePath, TextureLoadConfig &config);

    virtual void UseProgram() override;

    void SetModel(glm::mat4 newModel);
    void SetView(glm::mat4 newView) { view = newView; }
    void SetProjection(glm::mat4 newProjection) { projection = newProjection; }
  };
}
