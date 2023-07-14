#include <cstring>
#include <iostream>
#include "engine/render/Mesh.h"
#include "glad/glad.h"
namespace WEngine
{
  Mesh::Mesh() {}

  void Mesh::Init(float *vertices, int vCount, unsigned int *indices, int iCount)
  {
    // allocate memory for vao, vbo, ebo
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    if (vao == 0 || vbo == 0 || ebo == 0)
    {
      std::cout << "Error generating VAO, VBO, or EBO\n";
      abort();
    }

    indicesCount = iCount;
    glBindVertexArray(vao);

    // bind the vbo object to buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // copy data to the buffer, so there is no need to store the vertices variable as a member to this mesh, for now
    glBufferData(GL_ARRAY_BUFFER, vCount * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    // vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // vertex color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // vertex texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // set up ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount * sizeof(indices[0]), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void Mesh::Render()
  {
    glBindVertexArray(vao);
    if (wireframeMode)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  void Mesh::SetTransform(glm::mat4 transform)
  {
  }

  Mesh::~Mesh()
  {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
  }
}
