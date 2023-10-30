#include "engine/core/SceneManager.h"
#include "engine/core/FurryWolfEngine.h"

namespace WEngine {

	SceneManager::SceneManager() { engine = nullptr; }
	SceneManager* SceneManager::instance = nullptr;
	SceneManager::~SceneManager() { }

	void SceneManager::Init(FurryWolfEngine* engine) {
		Instance().engine = engine;
	}

	SceneManager& SceneManager::Instance() {
		if (instance == nullptr)
		{
			instance = new SceneManager();
		}
		return *instance;
	}

	void SceneManager::LoadScene(Scene* scene) {
		this->engine->State.scenes.clear();
		LoadSceneAdditive(scene);
	}

	void SceneManager::LoadSceneAdditive(Scene* scene) {
		scene->Load();
		scene->Start();
		this->engine->State.scenes.push_back(scene);
	}

	void SceneManager::Destroy() {
		delete instance;
	}
}
