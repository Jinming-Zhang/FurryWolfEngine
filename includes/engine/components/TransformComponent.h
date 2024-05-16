#pragma once
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/components/Component.h"

namespace WEngine {
    class TransformComponent : public Component {
    private:
        glm::vec3 position{};
        glm::vec3 rotation{};
        glm::vec3 scale{};

        glm::mat4 orientationMat{};

    public:
        TransformComponent();

        ~TransformComponent() override;

        glm::vec3 GetLocalPosition() const;

        void SetLocalPosition(glm::vec3 position);

        void SetLocalPosition(float x, float y, float z);

        void Translate(const glm::vec3 &offset);

        void SetLocalRotation(glm::vec3 eulerAngles);

        void SetLocalRotation(float x, float y, float z);

        void RotateAroundAxis(const glm::vec3 &axis, float degree);

        void RotateEulerAngles(glm::vec3 eulerAngle);

        void RotateEulerAngles(float pitch, float yaw, float roll);

        void SetLocalScale(glm::vec3 scale);

        void SetLocalScale(float x, float y, float z);

        glm::vec3 GetForward() const;

        glm::vec3 GetLeft() const;

        glm::vec3 GetUp() const;

        glm::mat3 GetBasis() const;

        glm::mat4 GetModel() const;
    };
}
