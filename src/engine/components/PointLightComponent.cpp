#include <iostream>
#include <string>
#include "engine/math/glm/glm.hpp"
#include "engine/core/FurryWolfEngine.h"
#include "engine/core/GameObject.h"
#include "engine/components/PointLightComponent.h"
#include "engine/components/TransformComponent.h"
namespace WEngine
{
  int PointLightComponent::PointLightIndexer = 0;
  PointLightComponent::PointLightComponent()
  {
    if (PointLightIndexer >= FurryWolfEngine::engineConfig.MAX_POINT_LIGHTS)
    {
      std::cout << "Maximum number of point light reached!\n";
#ifdef PERFETTO
      abort();
#endif
    }
    constant = 1.0f;
    linear = 0.09;
    quadratic = 0.032f;
    countId = PointLightComponent::PointLightIndexer;
  }

  PointLightComponent::~PointLightComponent() {}
  void PointLightComponent::Update(float deltaTime)
  {
    LightComponent::Update(deltaTime);

    intensity = 1.0f;
    std::string prefix{"pointLights["};
    prefix.append(std::to_string(countId));
    prefix.append("]");
    // base light
    glm::vec3 ambientStrength = color * intensity;
    shader->SetVec3(std::string{prefix + ".baseLight.ambient"}, ambientStrength.r, ambientStrength.b, ambientStrength.g);

    glm::vec3 diffuseStrength = color * 0.5f;
    shader->SetVec3(std::string{prefix + ".baseLight.diffuse"}, diffuseStrength.r, diffuseStrength.b, diffuseStrength.g);

    glm::vec3 specularStrength = 1.f * color;
    shader->SetVec3(std::string{prefix + ".baseLight.specular"}, specularStrength.r, specularStrength.b, specularStrength.g);

    // point light
    TransformComponent *transform = gameObject->GetComponent<TransformComponent *>();
    glm::vec3 pos = transform->Position();
    shader->SetVec3(std::string{prefix + ".position"}, pos.x, pos.y, pos.z);
    shader->SetFloat(std::string{prefix + ".constant"}, constant);
    shader->SetFloat(std::string{prefix + ".linear"}, linear);
    shader->SetFloat(std::string{prefix + ".quadratic"}, quadratic);
  }
}
