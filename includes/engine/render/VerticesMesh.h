#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/core/FurryWolfEngine.h"

#include "engine/components/TransformComponent.h"

#include "engine/render/Mesh.h"
#include "engine/render/ShaderProgram.h"
#include "engine/render/PhongShader.h"
#include "engine/render/materials/PhongModelMaterial.h"
namespace WEngine
{
  class VerticesMesh : public Mesh
  {
  private:
  public:
    VerticesMesh() : Mesh()
    {
    }
    virtual void Init(float *vertices, int count)
    {
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);

      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
      glEnableVertexAttribArray(0);
      // texture coordinate attribute
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
      glEnableVertexAttribArray(2);
      // normal
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
      glEnableVertexAttribArray(3);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      material = engine->defaultMaterial;
    }

    virtual void Update(float deltaTime) override
    {
      // if (TransformComponent *tf = gameObject->GetComponent<TransformComponent *>())
      // {
      // glm::mat4 &rot = tf->GetRotationMatrix();
      // rot = glm::rotate(rot, glm::radians(50.f) * deltaTime, glm::vec3(.5f, 1.f, .0f));
      // }
      Render();
    }

    virtual void Render() override
    {
      material->Use(gameObject);
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
