#pragma once
#include <vector>
#include "engine/core/GameObject.h"
namespace WEngine
{
	class GameObject;
	class FurryWolfEngine;
	class Scene
	{
		friend class SceneMaker;

	private:
		std::vector<GameObject*> gameobjects;
		FurryWolfEngine* engine;
		void CreateDefaultScene();
		int pointLightsCount = 0;
		int spointLightsCount = 0;

	public:
		Scene(FurryWolfEngine* engine);
		~Scene();
		void AddGameObject(GameObject* gameobject);
		int GetPointLightsCount();
		int GetSpotLightsCount();

		void Load();
		void Start();
		void AddPointLight() { ++pointLightsCount; }
		void AddSpotLight() { ++spointLightsCount; }
		void Refresh(float deltaTime);
		void DestroyScene();

		template <typename T>
		GameObject* FindObjectOfType()
		{
			for (auto go : gameobjects)
			{
				if (go->GetComponent<T>() != nullptr)
				{
					return go;
				}
			}
			return nullptr;
		}

		template <typename T>
		std::vector<GameObject*>FindObjectsOfType()
		{
			std::vector<GameObject*>result = std::vector<GameObject*>();
			for (auto go : gameobjects)
			{
				if (go->GetComponent<T>() != nullptr)
				{
					result.push_back(go);
				}
			}
			return result;
		}
	};

}
