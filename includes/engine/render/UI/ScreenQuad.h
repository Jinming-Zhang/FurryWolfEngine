#pragma once
#include "engine/render/meshes/IndexedDrawMesh.h"
namespace WEngine {
	class ScreenQuad
	{
	private:
		IndexedDrawMesh mesh{};
	public:
		ScreenQuad();
		~ScreenQuad();
		void Render();


	};

}
