#include "game/SceneSwitcher.h"
#include <cmath>
#include <iostream>


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/core/SceneManager.h"
#include "engine/core/SceneMaker.h"
#include "engine/inputs/InputSystem.h"

SceneSwitcher::SceneSwitcher() { }
SceneSwitcher::~SceneSwitcher() { }

int SceneSwitcher::index = 0;
void SceneSwitcher::NextScene() {
	++index;
	WEngine::SceneManager::Instance().LoadScene(WEngine::SceneMaker::GetSceneAt(index));
}

void SceneSwitcher::PreviousScene() {
	--index;
	index = std::max(0, index);
	WEngine::SceneManager::Instance().LoadScene(WEngine::SceneMaker::GetSceneAt(index));
}

void SceneSwitcher::Update(float deltaTime) {
	if (WEngine::InputSystem::Instance()->KeyPressed(GLFW_KEY_LEFT))
	{
		PreviousScene();
		std::cout << "Switch to previous scene\n";
	}
	else if (WEngine::InputSystem::Instance()->KeyPressed(GLFW_KEY_RIGHT))
	{
		NextScene();
		std::cout << "Switch to next scene\n";
	}
}
