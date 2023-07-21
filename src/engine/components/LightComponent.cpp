#include "engine/math/glm/glm.hpp"
#include "engine/core/GameObject.h"
#include "engine/components/LightComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/render/ShaderProgram.h"

namespace WEngine
{

  LightComponent::LightComponent()
  {
    color = glm::vec3{1.f};
    intensity = .1f;
  }

  LightComponent::~LightComponent() {}

  void LightComponent::Update(float deltaTime)
  {
    shader->UseProgram();
  }

  void LightComponent::SetShader(ShaderProgram *sp)
  {
    shader = sp;
  }
}