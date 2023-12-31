#pragma once
#include "engine/math/glm/glm.hpp"
namespace WEngine
{
	class GameObject;
	class FurryWolfEngine;
	class Scene;
	class GameObjectFactory
	{
	private:
	public:
		GameObjectFactory() = delete;
		~GameObjectFactory();
		static GameObject* CreateCamera(FurryWolfEngine* engine);
		static GameObject* CreateDirectionalLightGo(FurryWolfEngine* engine);
		static GameObject* CreatePointLightGo(FurryWolfEngine* engine, Scene* s = nullptr);
		static GameObject* CreateSpotLightGo(FurryWolfEngine* engine, Scene* s = nullptr);
		static GameObject* CreatePlaneMeshGO(FurryWolfEngine* engine);
		static GameObject* CreateCubeMeshGO(FurryWolfEngine* engine);
		static GameObject* CreateSphereMeshGO(FurryWolfEngine* engine, int segments = 8, int rings = 12);
		static glm::vec3 PolarToPoint(float theta, float phi, float radius);
	};
}
