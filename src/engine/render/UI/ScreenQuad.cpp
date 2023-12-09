#include "engine/render/UI/ScreenQuad.h"
#include <vector>
#include "engine/render//meshes/Mesh.h"
namespace WEngine {

	ScreenQuad::ScreenQuad()
	{
		std::vector<Vertex> quadVertices{
			Vertex{glm::vec3{-1.0f,1.0f,0.0f}, glm::vec3{0.0f,0.0f,1.0f}, glm::vec2{0.0f,1.0f}},
			Vertex{glm::vec3{-1.0f,-1.0f,0.0f}, glm::vec3{0.0f,0.0f,1.0f}, glm::vec2{0.0f,0.0f}},
			Vertex{glm::vec3{1.0f,-1.0f,0.0f}, glm::vec3{0.0f,0.0f,1.0f}, glm::vec2{1.0f,0.0f}},
			Vertex{glm::vec3{1.0f,1.0f,0.0f}, glm::vec3{0.0f,0.0f,1.0f}, glm::vec2{1.0f,1.0f}},
		};

		std::vector<unsigned int> quadIndices{
			0,1,2,
			0,2,3
		};
		mesh.Init(quadVertices, quadIndices);
	}

	ScreenQuad::~ScreenQuad()
	{
	}
	void ScreenQuad::Render()
	{
		mesh.Draw();
	}
}