#pragma once
#include "utils/Lights/Light.h"
class DirectionalLight :public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat r, GLfloat g, GLfloat b, GLfloat ambientIntensity,GLfloat diffuseIntensity, glm::vec3 direction);
	~DirectionalLight();
	virtual void UseLight(const UseLightData& data)override;
	void SetDirection(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 GetDirection()const;
private:
	glm::vec3 direction;
};

