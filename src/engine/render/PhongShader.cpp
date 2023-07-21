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
  void PhongShader::UseProgram()
  {
    ShaderProgram::UseProgram();

    // float g{sinf(glfwGetTime()) / 2.f + .5f};
    // int clrLocation{glGetUniformLocation(shaderProgramId, "ourColor")};
    // glUniform4f(clrLocation, .0f, g, .5f, 1.f);

    // // set textures
    // for (size_t i{0}; i < albedoTextures.size(); ++i)
    // {
    //   std::string texturePrefix{"texture"};
    //   albedoTextures.at(i)->Use(GL_TEXTURE0 + i);
    //   std::string textureStr{texturePrefix.append(std::to_string(i))};
    //   unsigned int uniformLocation = glGetUniformLocation(shaderProgramId, textureStr.c_str());
    //   glUniform1i(uniformLocation, i);
    // }
    // SetFloat("mixPct", .2f);
    // SetVec3("objectColor", 1.f, .5f, .31f);
    // SetVec3("lightColor", 1.f, 1.f, 1.f);
  }
}