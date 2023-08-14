#include <vector>
#include <iostream>

#include "glad/glad.h"

#include "engine/render/meshes/VerticesDrawMesh.h"

namespace WEngine
{
  VerticesDrawMesh::VerticesDrawMesh() : Mesh() {}
  VerticesDrawMesh::~VerticesDrawMesh()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
    vbo = 0;
  }

  bool VerticesDrawMesh::Init(const std::vector<Vertex> &vertices)
  {
    verticesCount = vertices.size();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    if (vao == 0 || vbo == 0)
    {
      std::cout << "Error generating VAO, VBO, or EBO\n";
      return false;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    Mesh::UploadVertexDataToVBO(vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
  }

  void VerticesDrawMesh::Draw()
  {
    if (wireframeMode)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
