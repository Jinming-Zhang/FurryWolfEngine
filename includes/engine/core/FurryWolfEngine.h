#pragma once

#include <vector>
#include <string>
#include <memory>
#include "engine/render/Material.h"
#include "engine/core/ResourceManager.h"

namespace WEngine
{
	class GameObject;
	class WolfGlfwWindow;
	class Mesh;
	class VerticesMesh;
	class Material;
	class CameraComponent;
	class Scene;

	struct WEngineConfig
	{
		int MAX_POINT_LIGHTS;
		int MAX_SPOT_LIGHTS;
	};

	struct EngineState {
		std::vector<Scene*> scenes;
	};

	class FurryWolfEngine
	{
		friend class SceneMaker;
		friend class Scene;
		friend class SceneManager;

	private:
		WolfGlfwWindow* window;
		EngineState State;
		std::vector<Scene*> scenes;

	public:
		FurryWolfEngine();
		~FurryWolfEngine();
		/// <summary>
		/// Initialize Engine systems and resources
		/// Such as ResourceManager and SceneManager
		/// Must be called before use.
		/// </summary>
		/// <returns></returns>
		bool Init();
		void Start();

	public:
		static WEngineConfig engineConfig;

	public:
		// resource creation methods
		template <typename T>
		T* CreateMaterial()
		{
			T* obj = new T();
			if (Material* mat = dynamic_cast<Material*>(obj))
			{
				mat->engine = this;
			}
			return obj;
		}

		GameObject* CreateGameObject(std::string name = "");

	private:
		void CreateScene();
	};
}
