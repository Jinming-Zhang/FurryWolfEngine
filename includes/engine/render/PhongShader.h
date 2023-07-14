#pragma once
#include <vector>
#include <string>
#include "engine/render/ShaderProgram.h"
#include "engine/render/Texture.h"
namespace WEngine
{
  class PhongShader : public ShaderProgram
  {
  private:
    std::vector<Texture *> albedoTextures;
    Texture *normalTexture;

  public:
    PhongShader();
    ~PhongShader();
    bool AddAlbedoTexture(std::string texturePath, TextureLoadConfig &config);
    bool SetNormalTexture(std::string texturePath, TextureLoadConfig &config);

    virtual void UseProgram() override;
  };
}
