#include <cstring>
#include <iostream>
#include "engine/render/Mesh.h"
#include "glad/glad.h"
namespace WEngine
{
  Mesh::Mesh() {}

  void Mesh::AssignVerticies(float *vertices, int count)
  {
    glGenVertexArrays(1, &vao);
    // allocate memory for vbo
    glGenBuffers(1, &vbo);
    if (vao == 0 || vbo == 0)
    {
      std::cout << "Error generating VAO or VBO\n";
      abort();
    }

    glBindVertexArray(vao);

    // bind the vbo object to buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // copy data to the buffer, so there is no need to store the vertices variable as a member to this mesh, for now
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void Mesh::UseMesh()
  {
  }
  void Mesh::Render()
  {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0);
  }
  Mesh::~Mesh()
  {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
  }
}
