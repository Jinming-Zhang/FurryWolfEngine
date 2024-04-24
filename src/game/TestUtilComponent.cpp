//
// Created by wolfy on 4/23/2024.
//

#include "game/TestUtilComponent.h"
#include "engine/core/ResourceManager.h"
#include "engine/inputs/InputSystem.h"
#include "GLFW/glfw3.h"

TestUtilComponent::TestUtilComponent() {
}

TestUtilComponent::~TestUtilComponent() {
}

void TestUtilComponent::Update(float deltaTime) {
    if (WEngine::InputSystem::Instance()->KeyPressed(GLFW_KEY_P)) {
        WEngine::ResourceManager::Instance()->PrintResourcesUsage();
    }
}
