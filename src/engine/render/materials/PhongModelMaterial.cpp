#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/ShaderProgram.h"
#include "engine/components/CameraComponent.h"

namespace WEngine
{
  PhongModelMaterial::PhongModelMaterial()
  {
    objColor = glm::vec3(1.f);
    shininess = 32.f;
    specularStrength = .5f;
  }
  PhongModelMaterial::~PhongModelMaterial() {}

  void PhongModelMaterial::Use(GameObject *go)
  {
    Material::Use(go);
    shaderToUse->SetVec3("material.ambient", objColor.r, objColor.g, objColor.b);
    shaderToUse->SetVec3("material.diffuse", objColor.r, objColor.g, objColor.b);
    shaderToUse->SetVec3("material.specular", specularStrength, specularStrength, specularStrength);

    shaderToUse->SetFloat("material.shininess", shininess);

    glm::vec3 camPos = CameraComponent::Main()->GetPosition();
    shaderToUse->UseProgram();
    shaderToUse->SetVec3("eyePos", camPos.x, camPos.y, camPos.z);
  }
}
