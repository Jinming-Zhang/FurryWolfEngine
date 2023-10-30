#include <vector>
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/core/FurryWolfEngine.h"
#include "engine/core/SceneMaker.h"

#include "engine/core/Scene.h"
#include "engine/core/GameObject.h"
#include "engine/window/IWindow.h"
#include "engine/window/WolfGlfwWindow.h"
#include "engine/inputs/InputSystem.h"
#include "engine/core/SceneManager.h"

#include "engine/render/Texture.h"

#include "engine/render/Shader.h"
#include "engine/render/PhongShader.h"
#include "engine/render/LightSourceShaderProgram.h"
#include "engine/render/Material.h"
#include "engine/render/materials/PhongModelMaterial.h"

#include "engine/components/SpotLightComponent.h"
#include "engine/components/PointLightComponent.h"

#include "engine/components/CameraComponent.h"

#include "engine/components/TransformComponent.h"

namespace WEngine
{
	WEngineConfig FurryWolfEngine::engineConfig = WEngineConfig{ 4, 4 };
	class TransformComponent;
	FurryWolfEngine::FurryWolfEngine()
	{
		scenes = std::vector<Scene*>();
		State = EngineState();
	}

	FurryWolfEngine::~FurryWolfEngine() {}

	bool FurryWolfEngine::Init()
	{
		std::cout << "Wolf Engine\n";
		window = new WEngine::WolfGlfwWindow{};

		if (!window->Init(800, 600, "0w0"))
		{
			std::cout << "Error loading gl\n";
			return false;
		}

		WEngine::InputSystem::Instance()->SetWindowContext(window);
#ifndef DEBUG
		WEngine::InputSystem::Instance()->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
		WEngine::SceneManager::Init(this);
		WEngine::SceneMaker::InitScenes(this);
		SceneManager::Instance().LoadScene(SceneMaker::GetSceneAt(0));
		return true;
	}

	void FurryWolfEngine::Start()
	{
		float currTime{ (float)glfwGetTime() };
		float prevTime = currTime;
		const float cap{ 1.f / 60.f };
		glEnable(GL_DEPTH_TEST);
		// glDepthFunc(GL_LESS);
		// glEnable(GL_STENCIL_TEST);
		// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		// glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		while (!window->ShouldClose())
		{
			currTime = glfwGetTime();
			if (currTime - prevTime < cap)
			{
				continue;
			}
			float delta = currTime - prevTime;
			prevTime = currTime;
			InputSystem::DeltaTime = delta;

			window->PollEvents();
			InputSystem::Instance()->Update();

			glClearColor(.2f, .3f, .3f, 1.f);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			// glEnable(GL_STENCIL_TEST);
			// glStencilMask(0xFF);
			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto scene : State.scenes)
			{
				scene->Refresh(delta);
			}
			window->SwapBuffers();
		}
	}

	GameObject* FurryWolfEngine::CreateGameObject(std::string name)
	{
		GameObject* go;
		if (name == "")
		{
			go = new GameObject();
		}
		else
		{
			go = new GameObject(name);
		}

		go->AddComponent<TransformComponent>();
		go->engine = this;
		return go;
	}

	void FurryWolfEngine::CreateScene()
	{
		// LoadScene(SceneMaker::MakeLotsCubeScene(this));
		// LoadScene(SceneMaker::MakeLightScene(this));
		// LoadScene(SceneMaker::MakeDepthVisualizationScene(this));
		//SceneManager::Instance().LoadScene(SceneMaker::MakeBlendingScene(this));
	}
}
