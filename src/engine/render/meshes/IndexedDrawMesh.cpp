#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "engine/render/meshes/IndexedDrawMesh.h"
namespace WEngine
{
  IndexedDrawMesh::IndexedDrawMesh() : Mesh() {}
  IndexedDrawMesh::~IndexedDrawMesh()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    vao = 0;
    vbo = 0;
    ebo = 0;
  }

  bool IndexedDrawMesh::Init(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
  {
    indicesCount = indices.size();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    if (vao == 0 || vbo == 0 || ebo == 0)
    {
      std::cout << "Error generating VAO, VBO, or EBO\n";
      return false;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    Mesh::UploadVertexDataToVBO(vertices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
  }

  void IndexedDrawMesh::Draw()
  {
    glBindVertexArray(vao);
    if (wireframeMode)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
