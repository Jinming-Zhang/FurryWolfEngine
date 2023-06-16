#pragma once
#include "GL/glew.h"
class Material
{
public:
	Material();
	Material(GLfloat ambientIntensity, GLfloat shininess);
	~Material();
	void UseMaterial(GLuint intensityLocation, GLuint shininessLocation);
private:
	GLfloat specularIntensity;
	// smoothness of the object
	// the higher, the clearer the reflection is
	GLfloat shininess;
};

