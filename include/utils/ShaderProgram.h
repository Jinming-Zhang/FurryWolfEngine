#pragma once
#include <string>
#include <unordered_map>
#include "GL/glew.h"
#include "utils/Lights/Light.h"
#include "utils/Lights/DirectionalLight.h"
#include "utils/Lights/PointLight.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void AddShader(const char* filePath, GLenum shaderType);
	void CompileShaders();
	void UseShader();
	void ClearShader();
	void SetDirectionalLight(Light* dLight);
	// matrices id getter
	const GLuint GetTransformMatId()const;
	const GLuint GetProjectionMatId()const;
	const GLuint GetViewMatId()const;
	const GLuint GetEyePositionId()const;
	// lighting model id getter
	const GLuint GetAmbientIntensityId();
	const GLuint GetAmbientColorId();
	const GLuint GetDirectionId();
	const GLuint GetDiffuseIntensityId();
	const GLuint GetSpecularIntensityId();
	const GLuint GetShininessId();
	// lights
	void AddPointLight(Light* pLight);
	void UsePointLights();
private:
	GLuint shaderId;
	GLuint projectionMatId;
	GLuint transformMatId;
	GLuint viewMatId;
	GLuint eyePositionId;

	GLuint ambientIntensityId;
	GLuint ambientColorId;
	GLuint diffuseIntensityId;
	GLuint directionId;
	GLuint specularIntensityId;
	GLuint shininessId;

	std::unordered_map<Light*, UseLightData> pointLights;
	std::string ReadFile(const char* path);
};

