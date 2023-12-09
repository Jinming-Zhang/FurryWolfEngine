#pragma once
namespace WEngine {
	class FrameBuffer
	{

	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();

		void Use();
		void UseTexture(int textureUnit);

	private:
		unsigned int bufferObj;
		unsigned int colorTexture;
		unsigned int renderBuffer;

	};

}
