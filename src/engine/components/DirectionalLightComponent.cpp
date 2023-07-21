#include "engine/math/glm/glm.hpp"
#include "engine/components/LightComponent.h"
#include "engine/components/DirectionalLightComponent.h"
namespace WEngine
{

  DirectionalLightComponent::DirectionalLightComponent()
  {
    direction = -1.f * glm::vec3(-.5f, -.5f, -.5f);
  }

  DirectionalLightComponent::~DirectionalLightComponent()
  {
  }

  void DirectionalLightComponent::Update(float deltaTime)
  {
    LightComponent::Update(deltaTime);

    glm::vec3 ambientStrength = color * intensity;
    shader->SetVec3("dLight.baseLight.ambient", ambientStrength.r, ambientStrength.b, ambientStrength.g);

    glm::vec3 diffuseStrength = color * .5f;
    shader->SetVec3("dLight.baseLight.diffuse", diffuseStrength.r, diffuseStrength.b, diffuseStrength.g);

    glm::vec3 specularStrength = 1.f * color;
    shader->SetVec3("dLight.baseLight.specular", specularStrength.r, specularStrength.b, specularStrength.g);

    shader->SetVec3("dLight.direction", direction.x, direction.y, direction.z);
  }
}
