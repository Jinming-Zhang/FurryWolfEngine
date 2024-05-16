#include <engine/math/glm/gtx/string_cast.hpp>
#include <gtest/gtest.h>
#include "engine/components/CameraComponent.h"
#include "engine/components/TransformComponent.h"

class TransformTest : public testing::Test {
protected:
    WEngine::TransformComponent transform;

    TransformTest() {
    }
};


TEST_F(TransformTest, Initialization) {
    glm::vec3 forward{transform.GetForward()};
    glm::vec3 left{transform.GetLeft()};
    glm::vec3 up{transform.GetUp()};
    EXPECT_FLOAT_EQ(forward.x, 0);
    EXPECT_FLOAT_EQ(forward.y, 0);
    EXPECT_FLOAT_EQ(forward.z, 1);

    EXPECT_FLOAT_EQ(left.x, 1);
    EXPECT_FLOAT_EQ(left.y, 0);
    EXPECT_FLOAT_EQ(left.z, 0);

    EXPECT_FLOAT_EQ(up.x, 0);
    EXPECT_FLOAT_EQ(up.y, 1);
    EXPECT_FLOAT_EQ(up.z, 0);
}

TEST_F(TransformTest, Translation) {
    transform.Translate(glm::vec3{1.0f});
    const glm::vec3 pos{transform.GetLocalPosition()};
    EXPECT_FLOAT_EQ(pos.x, 1.0f);
    EXPECT_FLOAT_EQ(pos.y, 1.0f);
    EXPECT_FLOAT_EQ(pos.z, 1.0f);

    transform.Translate(glm::vec3{1.0f, -1.0f, 0.0f});
    const glm::vec3 pos2{transform.GetLocalPosition()};
    EXPECT_FLOAT_EQ(pos2.x, 2.0f);
    EXPECT_FLOAT_EQ(pos2.y, 0.0f);
    EXPECT_FLOAT_EQ(pos2.z, 1.0f);
}

TEST_F(TransformTest, RotationForward90Y) {
    transform.RotateAroundAxis(glm::vec3{0.0f, 1.0f, 0.0f}, 90.0f);
    glm::vec3 forward{transform.GetForward()};
    glm::vec3 left{transform.GetLeft()};
    glm::vec3 up{transform.GetUp()};
    EXPECT_NEAR(forward.x, 1.0f, FLT_EPSILON);
    EXPECT_NEAR(forward.y, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(forward.z, 0.0f, FLT_EPSILON) << "current rotation" << glm::to_string(transform.GetBasis());

    EXPECT_NEAR(left.x, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(left.y, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(left.z, -1.0f, FLT_EPSILON);

    EXPECT_NEAR(up.x, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(up.y, 1.0f, FLT_EPSILON);
    EXPECT_NEAR(up.z, 0.0f, FLT_EPSILON);
}

TEST_F(TransformTest, RotationPositive90X) {
    transform.RotateAroundAxis(glm::vec3{1.0f, 0.0f, 0.0f}, 90.0f);
    glm::vec3 forward{transform.GetForward()};
    glm::vec3 left{transform.GetLeft()};
    glm::vec3 up{transform.GetUp()};
    EXPECT_NEAR(forward.x, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(forward.y, -1.0f, FLT_EPSILON);
    EXPECT_NEAR(forward.z, 0.0f, FLT_EPSILON) << "current rotation" << glm::to_string(transform.GetBasis());

    EXPECT_NEAR(left.x, 1.0f, FLT_EPSILON);
    EXPECT_NEAR(left.y, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(left.z, 0.0f, FLT_EPSILON);

    EXPECT_NEAR(up.x, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(up.y, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(up.z, 1.0f, FLT_EPSILON);
}

TEST_F(TransformTest, RotationPositive90Z) {
    transform.RotateAroundAxis(glm::vec3{0.0f, 0.0f, 1.0f}, 90.0f);
    glm::vec3 forward{transform.GetForward()};
    glm::vec3 left{transform.GetLeft()};
    glm::vec3 up{transform.GetUp()};
    EXPECT_NEAR(forward.x, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(forward.y, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(forward.z, 1.0f, FLT_EPSILON);

    EXPECT_NEAR(left.x, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(left.y, 1.0f, FLT_EPSILON);
    EXPECT_NEAR(left.z, 0.0f, FLT_EPSILON);

    EXPECT_NEAR(up.x, -1.0f, FLT_EPSILON);
    EXPECT_NEAR(up.y, 0.0f, FLT_EPSILON);
    EXPECT_NEAR(up.z, 0.0f, FLT_EPSILON);
}

TEST_F(TransformTest, RotationPositiveAxis) {
    transform.RotateAroundAxis(glm::vec3{1.0f}, 90.0f);

    glm::vec3 forward{transform.GetForward()};
    glm::vec3 left{transform.GetLeft()};
    glm::vec3 up{transform.GetUp()};

    EXPECT_NEAR(forward.x, 0.91f, 0.01f);
    EXPECT_NEAR(forward.y, -0.24f, 0.01f);
    EXPECT_NEAR(forward.z, 0.33f, 0.01f);

    EXPECT_NEAR(left.x, 0.33f, 0.01f);
    EXPECT_NEAR(left.y, 0.91f, 0.01f);
    EXPECT_NEAR(left.z, -0.24f, 0.01f);

    EXPECT_NEAR(up.x, -0.24f, 0.01f);
    EXPECT_NEAR(up.y, 0.33f, 0.01f);
    EXPECT_NEAR(up.z, 0.91f, 0.01f);
}

TEST_F(TransformTest, RotationMatrixAfterTranslation) {
    transform.Translate(glm::vec3{1.0f, 2.0f, 3.0f});
    transform.RotateAroundAxis(glm::vec3{1.0f}, 90.0f);
    transform.Translate(glm::vec3{1.0f, 2.0f, 3.0f});

    glm::vec3 forward{transform.GetForward()};
    glm::vec3 left{transform.GetLeft()};
    glm::vec3 up{transform.GetUp()};

    EXPECT_NEAR(forward.x, 0.91f, 0.01f);
    EXPECT_NEAR(forward.y, -0.24f, 0.01f);
    EXPECT_NEAR(forward.z, 0.33f, 0.01f);

    EXPECT_NEAR(left.x, 0.33f, 0.01f);
    EXPECT_NEAR(left.y, 0.91f, 0.01f);
    EXPECT_NEAR(left.z, -0.24f, 0.01f);

    EXPECT_NEAR(up.x, -0.24f, 0.01f);
    EXPECT_NEAR(up.y, 0.33f, 0.01f);
    EXPECT_NEAR(up.z, 0.91f, 0.01f);
}

TEST_F(TransformTest, ModelMatrix) {
    transform.Translate(glm::vec3{1.0f, 2.0f, 3.0f});
    transform.RotateAroundAxis(glm::vec3{1.0f}, 90.0f);
    transform.Translate(glm::vec3{1.0f, 2.0f, 3.0f});

    glm::mat4 mod = transform.GetModel();
    glm::vec4 point1{1.0f, 0.0f, 0.0f, 1.0f};
    glm::vec4 point2{0.0f, 1.0f, 0.0f, 1.0f};
    glm::vec4 point3{0.0f, 0.0f, 1.0f, 1.0f};


    glm::vec4 forward{mod * point3};
    glm::vec4 left{mod * point1};
    glm::vec4 up{mod * point2};

    glm::vec3 position{transform.GetLocalPosition()};
    EXPECT_FLOAT_EQ(position.x, 2.0f, FLT_EPSILON);
    EXPECT_FLOAT_EQ(position.y, 4.0f, FLT_EPSILON);
    EXPECT_FLOAT_EQ(position.z, 6.0f, FLT_EPSILON);

    EXPECT_NEAR(forward.x, 0.91f+2, 0.01f) << glm::to_string(mod);
    EXPECT_NEAR(forward.y, -0.24f+4, 0.01f);
    EXPECT_NEAR(forward.z, 0.33f+6, 0.01f);

    EXPECT_NEAR(left.x, 0.33f+2, 0.01f);
    EXPECT_NEAR(left.y, 0.91f+4, 0.01f);
    EXPECT_NEAR(left.z, -0.24f+6, 0.01f);

    EXPECT_NEAR(up.x, -0.24f+2, 0.01f);
    EXPECT_NEAR(up.y, 0.33f+4, 0.01f);
    EXPECT_NEAR(up.z, 0.91f+6, 0.01f);
}
