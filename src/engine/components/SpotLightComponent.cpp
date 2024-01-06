#include <iostream>
#include <string>

#include "engine/math/glm/glm.hpp"
#include "engine/core/FurryWolfEngine.h"
#include "engine/core/GameObject.h"
#include "engine/components/LightComponent.h"
#include "engine/components/SpotLightComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
namespace WEngine
{
  int SpotLightComponent::SpotLightIndexer = 0;
  SpotLightComponent::SpotLightComponent()
  {
    if (SpotLightIndexer >= FurryWolfEngine::engineConfig.MAX_SPOT_LIGHTS)
    {
      std::cout << "Maximum number of spot light reached!\n";
#ifdef PERFETTO
      abort();
#endif
    }
    direction = glm::vec3(.0f, .0f, -1.f);
    innerCutOffAngle = 12.5f;
    outterCutOffAngle = 18.f;
    countId = SpotLightComponent::SpotLightIndexer;
  }

  SpotLightComponent::~SpotLightComponent()
  {
  }
  void SpotLightComponent::Update(float deltaTime)
  {
    LightComponent::Update(deltaTime);

    std::string prefix{"spotLights["};
    prefix.append(std::to_string(countId));
    prefix.append("]");
    // base light
    glm::vec3 ambientStrength = color * intensity;
    shader->SetVec3(std::string{prefix + ".basePtLight.baseLight.ambient"}, ambientStrength.r, ambientStrength.b, ambientStrength.g);

    glm::vec3 diffuseStrength = color * .5f;
    shader->SetVec3(std::string{prefix + ".basePtLight.baseLight.diffuse"}, diffuseStrength.r, diffuseStrength.b, diffuseStrength.g);

    glm::vec3 specularStrength = 1.f * color;
    shader->SetVec3(std::string{prefix + ".basePtLight.baseLight.specular"}, specularStrength.r, specularStrength.b, specularStrength.g);

    // point light
    shader->SetFloat(std::string{prefix + ".basePtLight.constant"}, constant);
    shader->SetFloat(std::string{prefix + ".basePtLight.linear"}, linear);
    shader->SetFloat(std::string{prefix + ".basePtLight.quadratic"}, quadratic);
    // spot light
    CameraComponent *camera = CameraComponent::Main();
    if (camera)
    {
      glm::vec3 pos = camera->GetPosition();
      shader->SetVec3(std::string{prefix + ".basePtLight.position"}, pos.x, pos.y, pos.z);

      direction = camera->GetFront();

    }
    shader->SetVec3(std::string{prefix + ".direction"}, direction.x, direction.y, direction.z);
    shader->SetFloat(std::string{prefix + ".innerCutoffAngle"}, cosf(glm::radians(innerCutOffAngle)));
    shader->SetFloat(std::string{prefix + ".outterCutoffAngle"}, cosf(glm::radians(outterCutOffAngle)));
  }
}
