#pragma once
#include "engine/core/Scene.h"
#include "engine/core/FurryWolfEngine.h"

namespace WEngine {
	class SceneManager
	{
	private:
		FurryWolfEngine* engine;
		static SceneManager* instance;
		SceneManager();
	public:
		~SceneManager();
		static void Init(FurryWolfEngine* engine);
		static SceneManager& Instance();
		static void Destroy();

		void LoadScene(Scene* scene);
		void LoadSceneAdditive(Scene* scene);


	};

}
