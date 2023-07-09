#pragma once
#include "GL/glew.h"
#include "GLM/glm.hpp"
struct UseLightData
{
	// common light data
	GLfloat ambientIntensityLocation{ .0f };
	GLfloat diffuseIntensityLocation{ .0f };
	GLfloat colorLocation{ .0f };
	// directional light data
	GLfloat directionLocation{ .0f };
	// point light data
	GLfloat positionLocation{ .0f };
	GLfloat exponentLocation{ .0f };
	GLfloat linearLocation{ .0f };
	GLfloat constantLocation{ .0f };
};

class Light
{
public:
	Light();
	Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambientIntensity, GLfloat diffuseIntensity);
	~Light();
	void SetAmbientIntensity(GLfloat val);
	void SetDiffuseIntensity(GLfloat val);
	virtual void UseLight(const UseLightData& data);
protected:
	glm::vec3 color;
	GLfloat diffuseIntensity;
	GLfloat ambientIntensity;
};

