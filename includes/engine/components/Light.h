#pragma once
#include "engine/components/Component.h"
#include "engine/math/glm/glm.hpp"
namespace WEngine
{
  class Light : public Component
  {
  private:
    glm::vec3 color;

  public:
    Light(/* args */);
    glm::vec3 &GetColor() { return color; }
    ~Light();
  };

  Light::Light(/* args */)
  {
  }

  Light::~Light()
  {
  }

}
