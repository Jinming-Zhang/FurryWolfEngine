#include <functional>

#include "engine/core/GameObject.h"
#include "engine/components/Component.h"
#include "engine/components/meshes/MeshComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/PointLightComponent.h"
#include "engine/components/SpotLightComponent.h"

namespace WEngine
{
	int GameObject::idCounter = 0;
	GameObject::GameObject(std::string name)
	{
		components = std::vector<std::unique_ptr<Component>>();
		this->name = name;
	}

	void GameObject::Update(float deltaTime)
	{
		for (auto& com : components)
		{
			com->Update(deltaTime);
		}
	}
	void GameObject::FixedUpdate(float fixedDeltaTime)
	{
		for (auto& com : components)
		{
			com->FixedUpdate(fixedDeltaTime);
		}
	}
	void GameObject::LateUpdate(float deltaTime)
	{
		for (auto& com : components)
		{
			com->LateUpdate(deltaTime);
		}
	}
	void GameObject::Render()
	{
		MeshComponent* mesh = GetComponent<MeshComponent*>();
		if (mesh)
		{
			mesh->Render();
		}
	}

#ifndef WINDOWS
	template <>
	TransformComponent* GameObject::AddComponent<TransformComponent>()
	{
		std::unique_ptr<TransformComponent> cmp = std::make_unique<TransformComponent>();
		cmp->gameObject = this;
		cmp->engine = engine;
		cmp->transform = cmp.get();
		components.push_back(std::move(cmp));
		return (TransformComponent*)components[components.size() - 1].get();
	}

	template <>
	PointLightComponent* GameObject::AddComponent<PointLightComponent>()
	{
		std::unique_ptr<PointLightComponent> cmp = std::make_unique<PointLightComponent>();
		cmp->gameObject = this;
		cmp->engine = engine;
		cmp->transform = GetComponent<TransformComponent*>();
		++PointLightComponent::PointLightIndexer;
		components.push_back(std::move(cmp));
		return (PointLightComponent*)components[components.size() - 1].get();
	}

	template <>
	SpotLightComponent* GameObject::AddComponent<SpotLightComponent>()
	{
		std::unique_ptr<SpotLightComponent> cmp = std::make_unique<SpotLightComponent>();
		cmp->gameObject = this;
		cmp->engine = engine;
		cmp->transform = GetComponent<TransformComponent*>();
		++SpotLightComponent::SpotLightIndexer;
		components.push_back(std::move(cmp));
		return (SpotLightComponent*)components[components.size() - 1].get();
	}
#endif // !WINDOWS
}
