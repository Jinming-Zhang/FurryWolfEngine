#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/gtc/matrix_transform.hpp"
#include "engine/render/Mesh.h"
namespace WEngine
{
  class VerticesMesh : public Mesh
  {
  private:
  public:
    VerticesMesh(float *vertices, int count) : Mesh()
    {
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);

      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
      glEnableVertexAttribArray(0);
      // texture coordinate attribute
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
      glEnableVertexAttribArray(2);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }

    virtual void Update(float deltaTime) override
    {
      transform = glm::rotate(transform, glm::radians(50.f) * deltaTime, glm::vec3(.5f, 1.f, .0f));
    }

    virtual void Render() override
    {
      shaderToUse->SetModel(transform);
      shaderToUse->UseProgram();
      if (wireframeMode)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
      glBindVertexArray(vao);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glBindVertexArray(0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    ~VerticesMesh() {}
  };

}
