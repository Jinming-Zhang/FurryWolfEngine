#pragma once
#include <string.h>
#include "GL/glew.h"
#include "stb_image.h"
class Texture
{
public:
	Texture();
	Texture(std::string path);
	~Texture();
	void LoadTexture();
	void UseTexture();
	void ClearTexture();
private:
	GLuint textureId;
	int width;
	int height;
	int bitDepth;
	std::string filePath;
};
