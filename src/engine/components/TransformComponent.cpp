#include "engine/components/TransformComponent.h"

#include <engine/math/glm/detail/type_quat.hpp>
#include <engine/math/glm/gtx/quaternion.hpp>

#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

namespace WEngine {
    TransformComponent::TransformComponent() {
        position = glm::vec3{0.0f};
        rotation = glm::vec3{1.f};
        scale = glm::vec3{1.f};

        orientationMat = glm::mat4{1.0f};
    }

    TransformComponent::~TransformComponent() = default;

    glm::vec3 TransformComponent::GetLocalPosition() const {
        return position;
    }

    void TransformComponent::SetLocalPosition(glm::vec3 position) {
        this->position = position;
    }

    void TransformComponent::SetLocalPosition(float x, float y, float z) {
        this->position = glm::vec3{x, y, z};
    }

    void TransformComponent::Translate(const glm::vec3 &offset) {
        position += offset;
    }

    void TransformComponent::SetLocalRotation(glm::vec3 eulerAngles) {
        this->rotation = eulerAngles;
        this->orientationMat = glm::toMat4(glm::quat{eulerAngles});
    }

    void TransformComponent::SetLocalRotation(float x, float y, float z) {
        this->SetLocalRotation(glm::vec3{x, y, z});
    }

    void TransformComponent::RotateAroundAxis(const glm::vec3 &axis, float degree) {
        orientationMat = glm::rotate(orientationMat, glm::radians(degree), glm::normalize(axis));
    }

    void TransformComponent::RotateEulerAngles(glm::vec3 eulerAngle) {
        glm::quat q1{glm::toQuat(orientationMat)};
        glm::quat q2{eulerAngle};
        orientationMat = glm::toMat4(q2 * q1);
    }

    void TransformComponent::RotateEulerAngles(float pitch, float yaw, float roll) {
        this->RotateEulerAngles(glm::vec3{pitch, yaw, roll});
    }

    void TransformComponent::SetLocalScale(glm::vec3 scale) {
        this->scale = scale;
    }

    void TransformComponent::SetLocalScale(float x, float y, float z) {
        this->scale = glm::vec3{x, y, z};
    }

    glm::vec3 TransformComponent::GetForward() const {
        return glm::vec3{orientationMat[2]};
    }

    glm::vec3 TransformComponent::GetLeft() const {
        return glm::vec3{orientationMat[0]};
    }

    glm::vec3 TransformComponent::GetUp() const {
        return glm::vec3{orientationMat[1]};
    }

    glm::mat3 TransformComponent::GetBasis() const {
        return glm::mat3{orientationMat};
    }

    glm::mat4 TransformComponent::GetModel() const {
        glm::mat4 mod{orientationMat};
        mod = glm::scale(mod, scale);
        mod[3][0] = position.x;
        mod[3][1] = position.y;
        mod[3][2] = position.z;
        mod[3][3] = 1.0f;
        return mod;
    }
}
