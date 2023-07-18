#pragma once
#include <vector>
#include <string>
#include "glad/glad.h"
#include "engine/math/glm/glm.hpp"

#include "engine/render/ShaderProgram.h"

namespace WEngine
{
  class LightSourceShaderProgram : public ShaderProgram
  {
  private:
    glm::vec3 objectColor;
    glm::vec3 lightColor;

  public:
    LightSourceShaderProgram();
    ~LightSourceShaderProgram();
    glm::vec3 &GetObjectColor() { return objectColor; }
    glm::vec3 &GetLightColor() { return lightColor; }
    virtual void UseProgram() override;
  };


}
