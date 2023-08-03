#pragma once
#include "engine/math/glm/glm.hpp"
#include "engine/components/Component.h"
#include "engine/render/Material.h"

namespace WEngine
{
  /**
   * @brief Vertex struct contains basic information of a single vertex.
   *
   * @var Position Position of this vertex.
   * @var Normal Normal vector of this vertex.
   * @var TexCoords Texture coordinate of this vertex.
   */
  struct Vertex
  {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  class Mesh : public Component
  {
  protected:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int indicesCount;
    Material *material;
    class ShaderProgram *shaderToUse;

  public:
    bool wireframeMode = false;

  public:
    Mesh();
    void Init(float *verticies, int vCount, unsigned int *indices, int iCount);
    virtual void Update(float deltaTime) override;
    virtual void Render();
    void SetMaterial(Material *mat) { material = mat; }
    void SetShader(ShaderProgram *shader);

    ~Mesh();
  };
}
