#include <iostream>
#include <math.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"
#include "engine/math/glm/gtc/type_ptr.hpp"
#include "engine/util/stb_image.h"

#include "engine/render/PhongShader.h"

namespace WEngine
{
  PhongShader::PhongShader() : ShaderProgram()
  {
    albedoTextures = std::vector<Texture *>();
    normalTexture = nullptr;
  }

  PhongShader::~PhongShader()
  {
    for (auto texture : albedoTextures)
    {
      delete texture;
    }
    if (normalTexture != nullptr)
    {
      delete normalTexture;
    }
  }

  bool PhongShader::AddAlbedoTexture(std::string texturePath, TextureLoadConfig &config)
  {
    Texture *texture{new Texture{}};
    if (texture->LoadTexture(texturePath, config))
    {
      albedoTextures.push_back(texture);
      return true;
    }
    return false;
  }

  bool PhongShader::SetNormalTexture(std::string texturePath, TextureLoadConfig &config)
  {
    if (normalTexture != nullptr)
    {
      delete normalTexture;
    }
    normalTexture = new Texture{};
    return normalTexture->LoadTexture(texturePath, config);
  }
  void PhongShader::UseProgram() const
  {
    ShaderProgram::UseProgram();
  }
}
