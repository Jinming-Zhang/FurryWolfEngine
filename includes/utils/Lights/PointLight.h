#pragma once
#include "utils/Lights/Light.h"
class PointLight :public Light {
public:
	PointLight();
	PointLight(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 position, GLfloat exp, GLfloat lin, GLfloat cons);
	virtual void UseLight(const UseLightData& data)override;
	~PointLight();

private:
	glm::vec3 position;
	GLfloat exponent;
	GLfloat linear;
	GLfloat constant;
};
