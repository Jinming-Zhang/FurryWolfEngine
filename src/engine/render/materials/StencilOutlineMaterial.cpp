#include "glad/glad.h"
#include "engine/render/materials/StencilOutlineMaterial.h"
#include "engine/core/GameObject.h"
#include "engine/core/ResourceManager.h"
#include "engine/components/meshes/MeshComponent.h"

namespace WEngine
{
  StencilOutlineMaterial::StencilOutlineMaterial()
  {
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Outliner);
  }

  StencilOutlineMaterial::~StencilOutlineMaterial()
  {
  }
  void StencilOutlineMaterial::Use(GameObject *go)
  {
    MeshComponent *meshToDraw = go->GetComponent<MeshComponent *>();
    // draw object shaper to stencil buffer.
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::DepthVisualizer);
    Material::Use(go);
    meshToDraw->DrawMeshOnly();

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    shaderToUse = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Outliner);
    Material::Use(go);
    TransformComponent *tf = go->GetComponent<TransformComponent *>();
    glm::mat4 originalModel = tf->GetModel();
    glm::mat4 outlinerModel = glm::scale(originalModel, glm::vec3{1.1f});
    shaderToUse->SetMat4("model", outlinerModel);
    meshToDraw->DrawMeshOnly();

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
  }
}
