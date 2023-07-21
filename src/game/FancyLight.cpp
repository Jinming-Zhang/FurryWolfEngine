#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "game/FancyLight.h"
#include "engine/core/GameObject.h"
#include "engine/components/LightComponent.h"

FancyLight::FancyLight(/* args */)
{
}

void FancyLight::Update(float deltaTime)
{
  // WEngine::LightComponent *light = gameObject->GetComponent<WEngine::LightComponent *>();
  // if (light)
  // {
  //   glm::vec3 color;
  //   float time = static_cast<float>(glfwGetTime());
  //   color.x = sinf(time * 2.f);
  //   color.y = sinf(time * .7f);
  //   color.z = sinf(time * 1.3f);
  //   light->SetColor(color);
  // }
}
FancyLight::~FancyLight()
{
}
