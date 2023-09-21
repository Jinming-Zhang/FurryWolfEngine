#pragma once
#include "engine/components/meshes/MeshComponent.h"

namespace WEngine
{
  class GameObject;
  class MeshComponentFactory
  {
  private:
    /* data */
  public:
    MeshComponentFactory();
    ~MeshComponentFactory();
    static MeshComponent *AddPlaneMeshComponent(GameObject *parent);
    static MeshComponent *AddCubeMeshComponent(GameObject *parent);
    static MeshComponent *AddSphereMeshComponent(GameObject *parent, int segments = 8, int rings = 12);
  };

}
