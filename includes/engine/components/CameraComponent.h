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
		static CameraComponent* mainCam;

	public:
		CameraComponent();
		static CameraComponent* Main();
		static void SetMainCamera(CameraComponent* cam) { mainCam = cam; }
		void EnableRotation(bool enableRotation) { enableRotate = enableRotation; }
		~CameraComponent();

	private:
		bool enableRotate = true;
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
		virtual void LateUpdate(float deltaTime) override;

	public:
		// getter and setters
		const glm::mat4 GetClippedViewMatrix() const
		{
			return projection * calculateViewMatrix();
			return glm::ortho(.0f, 800.f, .0f, 600.f, .01f, 100.f) * calculateViewMatrix();
		}
		const glm::vec3& GetPosition() const { return position; }
		const glm::vec3& GetFront() const { return cameraFront; }

		void SetPosition(glm::vec3 pos)
		{
			position = pos;
		}
		void SetProjection(float fovDeg, float ratio, float near, float far);
	};

}
