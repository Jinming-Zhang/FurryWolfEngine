#pragma once
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/components/Component.h"

namespace WEngine {
    class TransformComponent : public Component {
    private:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 orientationMat;
        glm::mat4 rotationMatix;
        glm::mat4 model;

    public:
        TransformComponent();

        ~TransformComponent() override;

        const glm::vec3 &Position() const;

        glm::vec3 &Rotation();

        glm::vec3 &Scale();

        glm::mat4 &GetRotationMatrix();

        glm::mat4 GetModel();

        void SetModel(glm::mat4 model);

        void SetPosition(glm::vec3 position);

        void SetPosition(float x, float y, float z);

        void SetRotation(glm::vec3 rotation);

        void SetRotation(float x, float y, float z);

        void SetScale(glm::vec3 scale);

        void SetScale(float x, float y, float z);

        // new functions
        // operations
        void Translate(const glm::vec3 &offset);

        void Rotate(const glm::vec3 &axis, float degree);

        void Scale(const glm::vec3 &scalars);

        // getters
        glm::mat4 CalcModelMat();

        glm::vec3 GetForward() const;

        glm::vec3 GetLeft() const;

        glm::vec3 GetUp() const;

        glm::mat3 GetBasis() const;

        glm::mat4 GetTransformationMatrix() const;
    };
}
