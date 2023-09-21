#pragma once
#include <memory>
#include "engine/components/Component.h"
#include "engine/render/ShaderProgram.h"
#include "engine/math/glm/glm.hpp"

namespace WEngine
{
  class LightComponent : public Component
  {
  protected:
    glm::vec3 color;
    float intensity;
    ShaderProgram *shader;

  public:
    LightComponent();
    glm::vec3 &GetColor() { return color; }
    void SetColor(glm::vec3 newColor) { color = newColor; }
    void SetShader(ShaderProgram *shader) { this->shader = shader; }
    void SetIntensity(float newIntensity) { intensity = newIntensity; }

    ~LightComponent();

  public:
    virtual void Update(float deltaTime) override;
  };
}
