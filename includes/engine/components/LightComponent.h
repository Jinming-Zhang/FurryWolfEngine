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
    std::shared_ptr<ShaderProgram> shaderToUse;
    ShaderProgram *shader;

  public:
    LightComponent();
    glm::vec3 &GetColor() { return color; }
    void SetColor(glm::vec3 newColor) { color = newColor; }
    void SetShader(std::shared_ptr<ShaderProgram> shader) { shaderToUse = shader; }
    void SetShader(ShaderProgram *sp);

    ~LightComponent();

  public:
    virtual void Update(float deltaTime) override;
  };
}
