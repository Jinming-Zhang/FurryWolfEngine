#pragma once
#include <utility>
#include "glad/glad.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"
#include "engine/components/Component.h"
namespace WEngine
{
  class CameraComponent : public Component
  {
  private:
    static CameraComponent *mainCam;

  public:
    CameraComponent();
    static CameraComponent *Main();
    static void SetMainCamera(CameraComponent *cam) { mainCam = cam; }
    ~CameraComponent();

  private:
    // member variables
    glm::vec3 position;
    glm::vec3 camRight;
    glm::vec3 camUp;
    glm::vec3 camForward;

    glm::mat4 projection;
    glm::vec3 cameraTarget;

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

  public:
    // overrides
    virtual void LateUpdate(float deltaTime) override;

  public:
    // getter and setters
    const glm::mat4 GetClippedViewMatrix() const;
    const glm::mat4 GetProjectionMatrix() const;
    glm::mat4 GetViewMatrix() const;

    const glm::vec3 GetPosition() const;
    const glm::vec3 GetFront() const;

    void SetPosition(glm::vec3 pos);
    void SetProjection(float fovDeg, float ratio, float near, float far);
  };
}
