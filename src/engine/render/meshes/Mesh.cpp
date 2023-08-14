#include <cstring>
#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "engine/render/meshes/Mesh.h"

namespace WEngine
{
  Mesh::Mesh() {}
  Mesh::~Mesh() {}
  // definition for member function
  void Mesh::UploadVertexDataToVBO(const std::vector<Vertex>& vertices)
  {
    size_t verticesCount{vertices.size()};
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Vertex::Normal)));
    glEnableVertexAttribArray(1);

    // texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Vertex::TexCoords)));
    glEnableVertexAttribArray(2);
  }
}
