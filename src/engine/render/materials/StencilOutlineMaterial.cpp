#include "glad/glad.h"
#include "engine/render/materials/StencilOutlineMaterial.h"
#include "engine/core/GameObject.h"
#include "engine/render/meshes/Mesh.h"
namespace WEngine
{
  StencilOutlineMaterial::StencilOutlineMaterial(/* args */)
  {
  }

  StencilOutlineMaterial::~StencilOutlineMaterial()
  {
  }
  void StencilOutlineMaterial::Use(GameObject *go)
  {
    Material::Use(go);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    tmpMesh->Draw();
    
  }

}
