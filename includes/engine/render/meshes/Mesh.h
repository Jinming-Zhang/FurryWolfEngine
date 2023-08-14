#pragma once
#include <vector>
#include "engine/math/glm/glm.hpp"

namespace WEngine
{
  /**
   * @brief Vertex struct contains basic information of a single vertex.
   * @var Normal Normal vector of this vertex.
   * @var TexCoords Texture coordinate of this vertex.
   */
  struct Vertex
  {
    glm::vec3 Position; /**< Position of this vertex.*/
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  /**
   * @brief Mesh is the base class for different mesh types, which may have different render method, such as vertices draw or indexed draw, as well as how the mesh is interpreting and setup the vertex data/attributes.
   * @note
   * A Mesh object only contains the shape (vertices) of the object, the color and how the object should rendered are defined in Material.
   * To render a Mesh, a Material is required.(Usually Material will contains a Shader)
   *
   */
  class Mesh
  {
  public:
    bool wireframeMode = false;

  protected:
    void UploadVertexDataToVBO(const std::vector<Vertex> &vertices);

  public:
    Mesh();
    virtual void Draw() = 0;
    virtual ~Mesh();
  };
}
