#pragma once
#include "GL/glew.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	~Camera();

	void Update();
	void LateUpdate(const bool* keys, const float mouseXChange, const float mouseYChange);
	void SetMoveSpeed(GLfloat val);
	void SetTurnSpeed(GLfloat val);
	glm::vec3 GetPosition();
	glm::mat4 GetViewMatrix();
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat moveSpeed;
	GLfloat turnSpeed;

};

