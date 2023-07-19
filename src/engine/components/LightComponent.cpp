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
    TransformComponent *tf = gameObject->GetComponent<TransformComponent *>();
    glm::vec3 pos = tf->Position();
    shader->SetVec3("light.position", pos.x, pos.y, pos.z);

    glm::vec3 ambientStrength = color * intensity;
    shader->SetVec3("light.ambient", ambientStrength.r, ambientStrength.b, ambientStrength.g);

    glm::vec3 diffuseStrength = color*.5f;
    shader->SetVec3("light.diffuse", diffuseStrength.r, diffuseStrength.b, diffuseStrength.g);

    glm::vec3 specularStrength = 1.f * color;
    shader->SetVec3("light.specular", specularStrength.r, specularStrength.b, specularStrength.g);
  }

  void LightComponent::SetShader(ShaderProgram *sp)
  {
    shader = sp;
  }
}
