#pragma once
#include <utility>
#include "glad/glad.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"
#include "engine/components/Component.h"
namespace WEngine
{
  class Camera : public Component
  {
    // singleton
  private:
    static Camera *instance;
    Camera();

  public:
    static Camera *Main();
    ~Camera();

  private:
    // member variables
    glm::mat4 projection;
    glm::vec3 cameraTarget;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 position;
    float yaw;
    float pitch;
    float roll;
    float fov;
    float minFov;
    float maxFov;
    float fovSpeed;
    float yawSpeed;
    float pitchSpeed;
    float rollSpeed;
    bool freeCam;
    bool firstMouse;
    std::pair<float, float> prevMousePos;

    // move ment
    float moveSpeed;

  private:
    glm::mat4 calculateViewMatrix() const;
    glm::mat4 calculateViewMatrixManual(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) const;

  public:
    // overrides
    virtual void Update(float deltaTime) override;

  public:
    // getter and setters
    const glm::mat4 GetClippedViewMatrix() const
    {
      return projection * calculateViewMatrix();
    }
    const glm::vec3 &GetPosition() const { return position; }

    void SetPosition(glm::vec3 pos)
    {
      position = pos;
    }
    void SetProjection(float fovDeg, float ratio, float near, float far);
  };

}
