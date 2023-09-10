#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"

#include "engine/core/ResourceManager.h"

#include "engine/components/CameraComponent.h"
#include "engine/inputs/InputSystem.h"

namespace WEngine
{
  CameraComponent::CameraComponent()
  {
    fov = 45.f;
    minFov = 10.f;
    maxFov = 50.f;
    fovSpeed = 15.f;
    projection = glm::perspective(glm::radians(fov), 800.f / 600.f, .1f, 100.f);
    position = glm::vec3(.0f);
    cameraTarget = glm::vec3(.0f);
    cameraFront = glm::vec3(.0f, .0f, -1.f);
    cameraUp = glm::vec3(.0f, 1.f, .0f);

    yaw = 90.f;
    pitch = 0;
    roll = 0;
    yawSpeed = 10.0f;
    pitchSpeed = 10.0f;
    rollSpeed = 0;
    freeCam = true;

    moveSpeed = 5.f;
    prevMousePos = std::pair(400.0f, 300.0f);
    firstMouse = true;
  }
  CameraComponent::~CameraComponent() {}

  void CameraComponent::Update(float deltaTime)
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
    if (InputSystem::Instance()->KeyReleased(GLFW_KEY_R))
    {
      enableRotate = !enableRotate;
    }

    // notice the position is actually the opposite of where we are moving, since we really are moving all the objects in the scene in the opposite direction of where we want to move the camera.
    const float cameraSpeed{moveSpeed * deltaTime};
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_W))
    {
      position += cameraSpeed * cameraFront;
    }
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_S))
    {
      position -= cameraSpeed * cameraFront;
    }
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_A))
    {
      position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_D))
    {
      position += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_Q))
    {
      fov -= fovSpeed * deltaTime;
    }
    if (InputSystem::Instance()->KeyPressed(GLFW_KEY_E))
    {
      fov += fovSpeed * deltaTime;
    }
    fov = glm::clamp(fov, minFov, maxFov);

    projection = glm::perspective(glm::radians(fov), 800.f / 600.f, .1f, 100.f);
    if (!enableRotate)
    {
      return;
    }
    std::pair<float, float> mousePos = InputSystem::Instance()->GetMousePosition();
    std::pair<float, float> mouseDelta = std::pair(
        mousePos.first - prevMousePos.first,
        mousePos.second - prevMousePos.second);

    if (firstMouse)
    {
      firstMouse = false;
    }
    else
    {
      prevMousePos = mousePos;
    }

    yaw += mouseDelta.first * yawSpeed * deltaTime;
    pitch += mouseDelta.second * pitchSpeed * deltaTime;
    pitch = glm::clamp(pitch, -89.f, 89.f);
#ifdef VERBOSE
    if (mouseDelta.first + mouseDelta.second > 0.0001f)
    {
      printf("Mouse diff: %f, %f\n", mouseDelta.first, mouseDelta.second);
    }
#endif

    // calculate camera direction
    glm::vec3 direction{.0f};
    direction.x = cosf(glm::radians(yaw)) * cosf(glm::radians(pitch));
    direction.z = sinf(glm::radians(yaw)) * cosf(glm::radians(pitch));
    direction.y = sinf(glm::radians(pitch));

    cameraFront = glm::normalize(-direction);
  }

  glm::mat4 CameraComponent::calculateViewMatrix() const
  {
    if (freeCam)
    {
      // return glm::lookAt(position, position + cameraFront, cameraUp);
      return calculateViewMatrixManual(position, position + cameraFront, glm::vec3(.0f, 1.f, .0f));
    }
    else
    {
      // view = glm::lookAt(position, cameraTarget, glm::vec3(.0f, 1.f, .0f));
      return calculateViewMatrixManual(position, cameraTarget, glm::vec3(.0f, 1.f, .0f));
    }
  }

  glm::mat4 CameraComponent::calculateViewMatrixManual(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp) const
  {
    // calculate view coordinates
    // glm::vec3 zAxis = glm::normalize(target - pos);
    glm::vec3 zAxis = glm::normalize(pos - target);

    // right axis of view space
    // notice here that we need the camera to face the opposite direction of the positive z-axis, so that the cross product returns the positive right axis
    // other wise the cross product will return the negative right axis
    glm::vec3 rightAixs = glm::normalize(glm::cross(worldUp, zAxis));

    // up axis of view space
    glm::vec3 up{glm::normalize(glm::cross(zAxis, rightAixs))};

    // construct the view matrix with eye position
    glm::mat4 view = glm::mat4(1.f);
    glm::mat4 translation{1.f};
    translation[3][0] = -pos.x;
    translation[3][1] = -pos.y;
    translation[3][2] = -pos.z;

    view[0][0] = rightAixs.x;
    view[1][0] = rightAixs.y;
    view[2][0] = rightAixs.z;

    view[0][1] = up.x;
    view[1][1] = up.y;
    view[2][1] = up.z;

    view[0][2] = zAxis.x;
    view[1][2] = zAxis.y;
    view[2][2] = zAxis.z;
    glm::mat4 lookat = view * translation;
    // glm::vec4 viewedCoord = lookat * glm::vec4(-.5f, -.5f, .5f, 1.f);
    // printf("Position [-.5, -.5, .5, 1] in view coordinates: [%f, %f, %f, %f]\n", viewedCoord.x, viewedCoord.y, viewedCoord.z, viewedCoord.w);
    return lookat;
  }

  void CameraComponent::SetProjection(float fovDeg, float ratio, float near, float far)
  {
    projection = glm::perspective(glm::radians(fovDeg), ratio, near, far);
  }

  CameraComponent *CameraComponent::instance = nullptr;
  CameraComponent *CameraComponent::Main()
  {
    if (CameraComponent::instance == nullptr)
    {
      CameraComponent::instance = new CameraComponent();
    }
    return CameraComponent::instance;
  }
}
