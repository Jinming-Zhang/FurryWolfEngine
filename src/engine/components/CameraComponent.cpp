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

    glm::mat4 currentTransform{transform->GetModel()};
    glm::vec3 scale;
    glm::quat rotationQuat;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(currentTransform, scale, rotationQuat, translation, skew, perspective);
    std::cout << "CameraComponent translation [before]: " << glm::to_string(translation) << "\n";
    glm::mat4 rotationMat{glm::mat4{glm::mat3{currentTransform}}};
    rotationMat[3][3] = 1.0f;
    glm::vec3 rotationMatTranslation{rotationMat[3]};
    std::cout << "CameraComponent rotation mat [before]: " << glm::to_string(rotationMat) << "\n";
    glm::vec3 camRight{glm::normalize(rotationMat[0])};
    glm::vec3 camUp{glm::normalize(rotationMat[1])};
    glm::vec3 camForward{glm::normalize(rotationMat[2])};

    if (InputSystem::Instance()->KeyHold(GLFW_KEY_W))
    {
      translation -= cameraSpeed * camForward;
    }
    if (InputSystem::Instance()->KeyHold(GLFW_KEY_S))
    {
      translation += cameraSpeed * camForward;
    }
    if (InputSystem::Instance()->KeyHold(GLFW_KEY_A))
    {
      translation -= camRight * cameraSpeed;
    }
    if (InputSystem::Instance()->KeyHold(GLFW_KEY_D))
    {
      translation += camRight * cameraSpeed;
    }
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
    }
    else
    {
      float yawRot = mouseDelta.first * yawSpeed * deltaTime;
      float pitchRot = mouseDelta.second * pitchSpeed * deltaTime;
      if (glm::abs(yawRot) > 1)
      {
        rotationMat = glm::rotate(rotationMat, glm::radians(yawRot), glm::vec3{rotationMat[1]});
      }
      if (glm::abs(pitchRot) > 1)
      {
        // camRight = rotationMat[0];
        rotationMat = glm::rotate(rotationMat, glm::radians(pitchRot), glm::vec3{rotationMat[0]});
      }
    }

    rotationMatTranslation = glm::vec3{rotationMat[3]};
    std::cout << "CameraComponent translation [after]: " << glm::to_string(translation) << "\n";
    std::cout << "CameraComponent rotation mat [after]: " << glm::to_string(rotationMat) << "\n";
    glm::mat4 finalTranslateMat{1.0f};
    finalTranslateMat = glm::translate(finalTranslateMat, translation);
    // glm::mat4 newModel{glm::translate(rotationMat, translation)};
    glm::mat4 newModel{finalTranslateMat * rotationMat};
    glm::vec3 finalTranslation{newModel[3]};
    std::cout << "CameraComponent translation [final]: " << glm::to_string(finalTranslation) << "\n";
    std::cout << "CameraComponent model [final]: " << glm::to_string(newModel) << "\n";
    transform->SetModel(newModel);

#ifdef VERBOSE
    if (mouseDelta.first + mouseDelta.second > 0.0001f)
    {
      printf("Mouse diff: %f, %f\n", mouseDelta.first, mouseDelta.second);
    }
#endif
  }

  glm::mat4 CameraComponent::calculateViewMatrix() const
  {
    glm::mat4 orientation{glm::mat3{transform->GetModel()}};
    orientation[3][3] = 1.0f;
    glm::vec3 negTranslation{-glm::vec3{transform->GetModel()[3]}};
    return glm::translate(orientation, negTranslation);
    // if (freeCam)
    // {
    //   // return glm::lookAt(position, position + cameraFront, cameraUp);
    //   return calculateViewMatrixManual(position, position + cameraFront, glm::vec3(.0f, 1.f, .0f));
    // }
    // else
    // {
    //   // view = glm::lookAt(position, cameraTarget, glm::vec3(.0f, 1.f, .0f));
    //   return calculateViewMatrixManual(position, cameraTarget, glm::vec3(.0f, 1.f, .0f));
    // }
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
    // glm::vec3 negTranslation{};
    // glm::mat4 lookat = glm::translate(glm::mat4{glm::mat3{transform->GetModel()}}, translation);
    // glm::vec4 viewedCoord = lookat * glm::vec4(-.5f, -.5f, .5f, 1.f);
    // printf("Position [-.5, -.5, .5, 1] in view coordinates: [%f, %f, %f, %f]\n", viewedCoord.x, viewedCoord.y, viewedCoord.z, viewedCoord.w);
    return lookat;
  }

  const glm::mat4 CameraComponent::GetProjectionMatrix() const
  {
    return projection;
  }

  const glm::mat4 CameraComponent::GetViewMatrix() const
  {
    return calculateViewMatrix();
    // return calculateViewMatrixManual(position, cameraTarget, glm::vec3(.0f, 1.f, .0f));
  }

  void CameraComponent::SetProjection(float fovDeg, float ratio, float near, float far)
  {
    projection = glm::perspective(glm::radians(fovDeg), ratio, near, far);
  }

  const glm::vec3 CameraComponent::GetPosition() const
  {
    return transform->GetModel()[3];
  }

  const glm::vec3 CameraComponent::GetFront() const
  {
    return -(transform->GetModel()[2]);
  }

  void CameraComponent::SetPosition(glm::vec3 pos)
  {
    glm::mat3 orientation{transform->GetModel()};
    transform->SetModel(glm::translate(glm::mat4{orientation}, pos));
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
