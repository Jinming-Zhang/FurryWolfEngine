#include "engine/render/FrameBuffer.h"
#include "glad/glad.h"
#include <iostream>

namespace WEngine {
	FrameBuffer::FrameBuffer(int width, int height)
	{
		glGenFramebuffers(1, &bufferObj);
		glBindFramebuffer(GL_FRAMEBUFFER, bufferObj);

		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

		glGenRenderbuffers(1, &renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "Error Creating Framebuffer\n";
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &bufferObj);
		glDeleteTextures(1, &colorTexture);
		glDeleteRenderbuffers(1, &renderBuffer);
	}

	void FrameBuffer::Use()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, bufferObj);
	}
	void FrameBuffer::UseTexture(int textureUnit) {
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
	}
}