#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtx/matrix_decompose.hpp"
#include "engine/math/glm/gtx/quaternion.hpp"
#include "engine/math/glm/gtx/rotate_vector.hpp"
#include "engine/math/glm/gtx/string_cast.hpp"

#include "engine/core/ResourceManager.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/inputs/InputSystem.h"

namespace WEngine
{
  CameraComponent::CameraComponent()
  {
    position = glm::vec3{0.0f};
    camRight = glm::vec3{1.0f, 0.0f, 0.0f};
    camUp = glm::vec3{0.0f, 1.0f, 0.0f};
    camForward = glm::vec3{0.0f, 0.0f, 1.0f};

    fov = 45.f;
    minFov = 10.f;
    maxFov = 50.f;
    fovSpeed = 15.f;
    projection = glm::perspective(glm::radians(fov), 800.f / 600.f, .1f, 100.f);

    cameraTarget = glm::vec3(.0f);

    yawSpeed = 10.0f;
    pitchSpeed = 10.0f;
    rollSpeed = 0;
    freeCam = true;

    moveSpeed = 5.f;
    prevMousePos = std::pair(400.0f, 300.0f);
    firstMouse = true;
  }

  CameraComponent::~CameraComponent() {}

  void CameraComponent::LateUpdate(float deltaTime)
  {
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_P))
    {
      ResourceManager::Instance()->PrintResourcesUsage();
    }

    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_EQUAL))
    {
      moveSpeed += 1;
    }
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_MINUS))
    {
      moveSpeed -= 1;
    }

    // notice the position is actually the opposite of where we are moving, since we really are moving all the objects in the scene in the opposite direction of where we want to move the camera.
    const float cameraSpeed{moveSpeed * deltaTime};
    glm::vec3 xMovement{0.0f};
    glm::vec3 zMovement{0.0f};
    if (InputSystem::Instance()->KeyHold(GLFW_KEY_W))
    {
      zMovement = -camForward * cameraSpeed;
    }

    if (InputSystem::Instance()->KeyHold(GLFW_KEY_S))
    {
      zMovement = camForward * cameraSpeed;
    }

    if (InputSystem::Instance()->KeyHold(GLFW_KEY_A))
    {
      xMovement = -camRight * cameraSpeed;
    }
    if (InputSystem::Instance()->KeyHold(GLFW_KEY_D))
    {
      xMovement = camRight * cameraSpeed;
    }
    position += xMovement;
    position += zMovement;

    if (InputSystem::Instance()->KeyHold(GLFW_KEY_Q))
    {
      fov -= fovSpeed * deltaTime;
    }
    if (InputSystem::Instance()->KeyHold(GLFW_KEY_E))
    {
      fov += fovSpeed * deltaTime;
    }
    fov = glm::clamp(fov, minFov, maxFov);

    projection = glm::perspective(glm::radians(fov), 800.f / 600.f, .1f, 100.f);

    // calculation new rotation based on mouse input
    std::pair<float, float> mousePos = InputSystem::Instance()->GetMousePosition();
    std::pair<float, float> mouseDelta = std::pair(
        mousePos.first - prevMousePos.first,
        mousePos.second - prevMousePos.second);
    prevMousePos = mousePos;
    if (firstMouse)
    {
      firstMouse = false;
      return;
    }
    float yawRot = mouseDelta.first * yawSpeed * deltaTime;
    float pitchRot = mouseDelta.second * pitchSpeed * deltaTime;
    if (glm::abs(yawRot) > 1)
    {
      camRight = glm::rotate(camRight, -glm::radians(yawRot), camUp);
      camRight = glm::normalize(camRight);
      camForward = glm::cross(camRight, camUp);
    }
    if (glm::abs(pitchRot) > 1)
    {
      camUp = glm::rotate(camUp, -glm::radians(pitchRot), camRight);
      camUp = glm::normalize(camUp);
      camForward = glm::cross(camRight, camUp);
    }

#ifdef VERBOSE
    if (mouseDelta.first + mouseDelta.second > 0.0001f)
    {
      printf("Mouse diff: %f, %f\n", mouseDelta.first, mouseDelta.second);
    }
#endif
  }

  const glm::mat4 CameraComponent::GetProjectionMatrix() const
  {
    return projection;
  }

  glm::mat4 CameraComponent::GetViewMatrix() const
  {
    glm::mat4 view{1.0f};
    glm::mat4 translation{1.0f};
    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    view[0][0] = camRight.x;
    view[1][0] = camRight.y;
    view[2][0] = camRight.z;

    view[0][1] = camUp.x;
    view[1][1] = camUp.y;
    view[2][1] = camUp.z;

    view[0][2] = camForward.x;
    view[1][2] = camForward.y;
    view[2][2] = camForward.z;
    return view * translation;
  }
  const glm::mat4 CameraComponent::GetClippedViewMatrix() const
  {
    return GetProjectionMatrix() * GetViewMatrix();
  }

  void CameraComponent::SetProjection(float fovDeg, float ratio, float near, float far)
  {
    projection = glm::perspective(glm::radians(fovDeg), ratio, near, far);
  }

  const glm::vec3 CameraComponent::GetPosition() const
  {
    return position;
  }

  const glm::vec3 CameraComponent::GetFront() const
  {
    return -camForward;
  }

  void CameraComponent::SetPosition(glm::vec3 pos)
  {
    position = pos;
  }

  CameraComponent *CameraComponent::mainCam = nullptr;
  CameraComponent *CameraComponent::Main()
  {
    if (CameraComponent::mainCam == nullptr)
    {
      CameraComponent::mainCam = new CameraComponent();
    }
    return CameraComponent::mainCam;
  }
}
