#include "glad/glad.h"
#include "engine/components/IndexedDrawMeshComponent.h"
namespace WEngine
{
  IndexedDrawMeshComponent::IndexedDrawMeshComponent() {}
  IndexedDrawMeshComponent::~IndexedDrawMeshComponent() {}

  bool IndexedDrawMeshComponent::Init(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
  {
    indicesCount = indices.size();

    // generate buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    if (vao == 0 || vbo == 0 || ebo == 0)
    {
      std::cout << "Error generating VAO, VBO, or EBO\n";
      abort();
    }

    // bind buffers
    glBindVertexArray(vao);

    // upload vertices data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // setup vertex attributes
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);
    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Vertex::Normal));
    glEnableVertexAttribArray(1);
    // texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Vertex::TexCoords));
    glEnableVertexAttribArray(2);

    // set up ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
  }
  void IndexedDrawMeshComponent::Update(float deltaTime)
  {
    Render();
  }

  void IndexedDrawMeshComponent::Render()
  {
    // material->Use(gameObject);
    phongMat->Use(gameObject);
    glBindVertexArray(vao);
    if (wireframeMode)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  void IndexedDrawMeshComponent::SetPhongMaterial(PhongModelMaterial *mat)
  {
    phongMat = mat;
  }
}
