#include "engine/render/Material.h"
#include "engine/render/ShaderProgram.h"
#include "engine/core/GameObject.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"

namespace WEngine
{
  Material::Material(/* args */)
  {
  }

  Material::~Material()
  {
  }
  void Material::Use(GameObject *go)
  {
    shaderToUse->UseProgram();
    TransformComponent *tf = go->GetComponent<TransformComponent *>();
    shaderToUse->SetMat4("model", tf->CalcModelMat());

    glm::mat4 view = CameraComponent::Main()->GetClippedViewMatrix();
    shaderToUse->SetMat4("cameraMatrix", view);
  }
}
