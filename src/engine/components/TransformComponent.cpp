#include "engine/components/TransformComponent.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

namespace WEngine {
    TransformComponent::TransformComponent(/* args */) {
        position = glm::vec3{0.0f};
        rotationMatix = glm::mat4{1.f};
        orientationMat = glm::mat4{1.0f};
        rotation = glm::vec3{1.f};
        scale = glm::vec3{1.f};
        model = glm::mat4{1.f};
    }

    TransformComponent::~TransformComponent() {
    }


    void TransformComponent::SetPosition(glm::vec3 position) {
        this->position = position;
    }

    void TransformComponent::SetPosition(float x, float y, float z) {
        this->position = glm::vec3{x, y, z};
    }

    void TransformComponent::SetRotation(glm::vec3 rotation) {
        this->rotation = rotation;
    }

    void TransformComponent::SetRotation(float x, float y, float z) {
        this->rotation = glm::vec3{x, y, z};
    }

    void TransformComponent::SetScale(glm::vec3 scale) {
        this->scale = scale;
    }

    void TransformComponent::SetScale(float x, float y, float z) {
        this->scale = glm::vec3{x, y, z};
    }


    glm::mat4 &TransformComponent::GetRotationMatrix() {
        return rotationMatix;
    }

    glm::mat4 TransformComponent::GetModel() {
        return model;
    }

    void TransformComponent::SetModel(glm::mat4 model) {
        this->model = model;
    }

    glm::mat4 TransformComponent::CalcModelMat() {
        return model;
        model = glm::mat4{1.f};
        model = glm::translate(model, position);

        model = glm::scale(model, scale);

        // model = glm::rotate(model, glm::radians(scale.x), glm::vec3(1.f, .0f, .0f));
        // model = glm::rotate(model, glm::radians(scale.y), glm::vec3(.0f, 1.f, .0f));
        // model = glm::rotate(model, glm::radians(scale.z), glm::vec3(.0f, .0f, 1.f));

        model = model * rotationMatix;
        return model;
    }

    void TransformComponent::Translate(const glm::vec3 &offset) {
        position += offset;
    }

    void TransformComponent::Rotate(const glm::vec3 &axis, float degree) {
        orientationMat = glm::rotate(orientationMat, glm::radians(degree), glm::normalize(axis));
    }

    void TransformComponent::Scale(const glm::vec3 &scalars) {
    }

    const glm::vec3 &TransformComponent::Position() const {
        return position;
    }

    glm::vec3 &TransformComponent::Rotation() {
        return rotation;
    }

    glm::vec3 &TransformComponent::Scale() {
        return scale;
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

    glm::mat4 TransformComponent::GetTransformationMatrix() const {
        glm::mat4 mod{1.0f};
        mod = glm::scale(mod, scale);
        mod = orientationMat * mod;
        mod = glm::translate(mod, position);
        return mod;
    }
}
