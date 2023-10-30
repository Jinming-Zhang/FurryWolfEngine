#pragma once
#include "engine/components/Component.h"
class SceneSwitcher :public WEngine::Component
{
private:
	static int index;
public:
	SceneSwitcher();
	~SceneSwitcher();
	void Update(float deltaTime)override;
	void NextScene();
	void PreviousScene();
};

