#include "engine/components/TransformComponent.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

namespace WEngine
{
  TransformComponent::TransformComponent(/* args */)
  {
    position = glm::vec3{1.f};
    rotationMatix = glm::mat4{1.f};
    rotation = glm::vec3{1.f};
    scale = glm::vec3{1.f};
    model = glm::mat4{1.f};
  }

  TransformComponent::~TransformComponent() {}

  glm::vec3 &TransformComponent::Position()
  {
    return position;
  }
  glm::vec3 &TransformComponent::Rotation()
  {
    return rotation;
  }
  glm::vec3 &TransformComponent::Scale()
  {
    return scale;
  }
  void TransformComponent::SetPosition(glm::vec3 position)
  {
    this->position = position;
  }
  void TransformComponent::SetPosition(float x, float y, float z)
  {
    this->position = glm::vec3{x, y, z};
  }
  void TransformComponent::SetRotation(glm::vec3 rotation)
  {
    this->rotation = rotation;
  }
  void TransformComponent::SetRotation(float x, float y, float z)
  {
    this->rotation = glm::vec3{x, y, z};
  }
  void TransformComponent::SetScale(glm::vec3 scale)
  {
    this->scale = scale;
  }
  void TransformComponent::SetScale(float x, float y, float z)
  {
    this->scale = glm::vec3{x, y, z};
  }
  glm::mat4 &TransformComponent::GetRotationMatrix()
  {
    return rotationMatix;
  }

  glm::mat4 TransformComponent::GetModel()
  {
    return model;
  }
  void TransformComponent::SetModel(glm::mat4 model)
  {
    this->model = model;
  }

  glm::mat4 TransformComponent::CalcModelMat()
  {
    return model;
    model = glm::mat4{1.f};
    model = glm::translate(model, position);

    model = glm::scale(model, scale);

    // model = glm::rotate(model, glm::radians(scale.x), glm::vec3(1.f, .0f, .0f));
    // model = glm::rotate(model, glm::radians(scale.y), glm::vec3(.0f, 1.f, .0f));
    // model = glm::rotate(model, glm::radians(scale.z), glm::vec3(.0f, .0f, 1.f));

    model = model * rotationMatix;
    return model;
  }
}
