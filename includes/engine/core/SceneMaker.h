#pragma once

#include "engine/core/FurryWolfEngine.h"
#include "engine/core/ResourceManager.h"
#include "engine/core/GameObject.h"
#include "engine/core/Scene.h"
#include "engine/core/GameObjectFactory.h"
#include "engine/core/MeshComponentFactory.h"

#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/LightComponent.h"
#include "engine/components/DirectionalLightComponent.h"
#include "engine/components/PointLightComponent.h"
#include "engine/components/SpotLightComponent.h"

#include "engine/render/meshes/Mesh.h"
#include "engine/components/meshes/MeshComponent.h"
#include "engine/components/meshes/IndexedDrawMeshComponent.h"
#include "engine/components/meshes/VerticesDrawMeshComponent.h"
#include "engine/components/meshes/ModelComponent.h"

#include "engine/render/LightSourceShaderProgram.h"

#include "engine/render/Material.h"
#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/materials/SimpleUnlitMaterial.h"
#include "engine/render/materials/LightSourceMaterial.h"
#include "engine/render/materials/DepthVisualizerMaterial.h"
#include "engine/render/materials/StencilOutlineMaterial.h"

#include "game/FancyLight.h"
#include "game/SceneSwitcher.h"

namespace WEngine
{
	class SceneMaker
	{
	private:
		static glm::vec3 cubePositions[];
		static std::vector<Scene*> availableScenes;

	public:
		SceneMaker() {}
		static void InitScenes(FurryWolfEngine* engine);
		static Scene* GetSceneAt(int index);
		static Scene* MakeLotsCubeScene(FurryWolfEngine* engine);
		static Scene* MakeLightScene(FurryWolfEngine* engine);
		static Scene* MakeDepthVisualizationScene(FurryWolfEngine* engine);
		static Scene* MakeBlendingScene(FurryWolfEngine* engine);
		~SceneMaker() {}
	}; // end class declaration
}
