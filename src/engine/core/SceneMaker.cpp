#include "engine/core/SceneMaker.h"
#include "engine/components/SkyboxComponent.h"

namespace WEngine {
    std::vector<Scene *> SceneMaker::availableScenes = std::vector<Scene *>();

    void SceneMaker::InitScenes(FurryWolfEngine *engine) {
        availableScenes = std::vector<Scene *>();
        availableScenes.push_back(MakeDepthVisualizationScene(engine));
        availableScenes.push_back(MakeLotsCubeScene(engine));
        availableScenes.push_back(MakeLightScene(engine));
        availableScenes.push_back(MakeBlendingScene(engine));

        for (auto scene: availableScenes) {
            GameObject *switcher = engine->CreateGameObject("Scene Switcher");
            switcher->AddComponent<SceneSwitcher>();
            scene->AddGameObject(switcher);
        }
    }

    Scene *SceneMaker::GetSceneAt(int index) {
        index = index % availableScenes.size();
        Scene *s = availableScenes.at(index);
        return s;
    }

    Scene *SceneMaker::MakeLotsCubeScene(FurryWolfEngine *engine) {
        Scene *s = new Scene(engine);
        for (size_t i{0}; i < 10; ++i) {
            GameObject *go = GameObjectFactory::CreateCubeMeshGO(engine);
            s->AddGameObject(go);
            // set transform
            TransformComponent *transform = go->GetComponent<TransformComponent *>();
            glm::vec3 pos = cubePositions[i];
            transform->Translate(pos);
            transform->RotateAroundAxis(glm::vec3(1.0f, 0.3f, 0.5f), glm::radians(i * 20.0f));
            // set material
            SimpleUnlitMaterial *mat = engine->CreateMaterial<SimpleUnlitMaterial>();
            mat->AddAlbedoMap(
                ResourceManager::Instance()->LoadTexture<Texture>("assets/images/textures/container2.png"));
            mat->AddAlbedoMap(
                ResourceManager::Instance()->LoadTexture<Texture>("assets/images/textures/awesomeface.png"));
            // mat->AddSpecularMap(ResourceManager::Instance()->LoadTexture<Texture>("assets/images/textures/container2_specular.png"));
            MeshComponent *mesh = go->GetComponent<MeshComponent *>();
            mesh->SetMaterial(mat);
        }
        return s;
    }

    Scene *SceneMaker::MakeLightScene(FurryWolfEngine *engine) {
        Scene *s = new Scene(engine);

        ShaderProgram *phongShader = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong);

        SpotLightComponent *flashLight = CameraComponent::Main()->gameObject->AddComponent<SpotLightComponent>();
        s->AddSpotLight();
        flashLight->SetShader(phongShader);
        flashLight->SetColor(glm::vec3(1.f));

        // directional light source
        GameObject *lightGo = s->FindObjectOfType<DirectionalLightComponent *>();
        if (lightGo) {
            lightGo->GetComponent<DirectionalLightComponent *>()->SetIntensity(0.1f);
            TransformComponent *lightGoTransform{lightGo->GetComponent<TransformComponent *>()};
            lightGoTransform->Translate(glm::vec3(1.2f, 1.f, 2.f));
            lightGoTransform->SetLocalScale(glm::vec3(.2f));
            // light source mesh
            MeshComponent *lightMesh = MeshComponentFactory::AddCubeMeshComponent(lightGo);
            LightSourceMaterial *lightGoMat = engine->CreateMaterial<LightSourceMaterial>();
            lightMesh->SetMaterial(lightGoMat);
            lightGoMat->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
        }

        // point lights
        glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f, 0.2f, -8.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f, 2.0f, -12.0f),
            glm::vec3(0.0f, 0.0f, -3.0f)
        };

        for (int i = 0; i < 4; ++i) {
            GameObject *pLightGO = GameObjectFactory::CreatePointLightGo(engine);
            s->AddGameObject(pLightGO);
            s->AddPointLight();
            // mesh
            MeshComponent *pMesh = MeshComponentFactory::AddCubeMeshComponent(pLightGO);
            LightSourceMaterial *lightGoMat = engine->CreateMaterial<LightSourceMaterial>();
            pMesh->SetMaterial(lightGoMat);

            PointLightComponent *pLightCmp = pLightGO->GetComponent<PointLightComponent *>();
            pLightCmp->SetShader(phongShader);
            glm::vec3 pLightColor = glm::vec3(i * .25f);
            pLightCmp->SetColor(pLightColor);
            lightGoMat->SetColor(pLightColor);
            pLightCmp->transform->Translate(pointLightPositions[i]);
        }

        // toy
        // material
        PhongModelMaterial *phongMat = engine->CreateMaterial<PhongModelMaterial>();
        std::string albedoPath{"assets/images/textures/container2.png"};
        std::string specularPath{"assets/images/textures/container2_specular.png"};
        auto albedoMap1 = ResourceManager::Instance()->LoadTexture<Texture>(albedoPath);
        auto specularMap1 = ResourceManager::Instance()->LoadTexture<Texture>(specularPath);
        phongMat->AddAlbedoMap(albedoMap1);
        phongMat->AddSpecularMap(specularMap1);
        phongMat->SetBaseColor(0.0f, 1.0f, 1.0f);

        for (size_t i{0}; i < 10; ++i) {
            GameObject *toy = engine->CreateGameObject("Toy No " + std::to_string(i));
            s->AddGameObject(toy);
            MeshComponent *vMesh = MeshComponentFactory::AddCubeMeshComponent(toy);
            vMesh->SetMaterial(phongMat);
            TransformComponent *transform = toy->GetComponent<TransformComponent *>();
            transform->SetLocalPosition(cubePositions[i]);
            transform->RotateAroundAxis(glm::vec3(1.f, .3f, .5f), i * 20.0f);
        }

        // import model
        GameObject *backpackModel = engine->CreateGameObject("Backpack");
        s->AddGameObject(backpackModel);
        ModelComponent *modelCmp = backpackModel->AddComponent<ModelComponent>();
        modelCmp->Init("./assets/models/backpack/backpack.obj");
        // modelCmp->Init("./assets/models/obj/Wolf_obj.obj");
        TransformComponent *backpackTf = backpackModel->GetComponent<TransformComponent *>();
        backpackTf->Translate(glm::vec3(0.f, 0.f, -1.f));
        backpackTf->SetLocalScale(glm::vec3(0.5f));
        return s;
    }

    Scene *SceneMaker::MakeDepthVisualizationScene(FurryWolfEngine *engine) {
        Scene *s = new Scene(engine);
        // skybox
        GameObject *skybox{engine->CreateGameObject("Default Skybox")};
        skybox->AddComponent<SkyboxComponent>();
        s->AddGameObject(skybox);

        // dlight
        ShaderProgram *lightSourceSp = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::LightSource);
        ShaderProgram *phongShader = &ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong);

        GameObject *lightGo = engine->CreateGameObject();
        s->AddGameObject(lightGo);
        TransformComponent *lightGoTf{lightGo->GetComponent<TransformComponent *>()};
        lightGoTf->Translate(glm::vec3(1.2f, 1.f, 2.f));
        lightGoTf->SetLocalScale(glm::vec3(.2f));

        // light source mesh
        MeshComponent *lightMesh = MeshComponentFactory::AddCubeMeshComponent(lightGo);
        LightSourceMaterial *lightGoMat = engine->CreateMaterial<LightSourceMaterial>();
        lightGoMat->SetShader(lightSourceSp);
        lightMesh->SetMaterial(lightGoMat);

        // light component
        GameObject *dLightGo = s->FindObjectOfType<DirectionalLightComponent *>();
        if (dLightGo) {
            DirectionalLightComponent *dLight = dLightGo->GetComponent<DirectionalLightComponent *>();
            dLight->SetShader(phongShader);
            glm::vec3 dLightColor = glm::vec3(1.f, 1.f, 1.f);
            dLight->SetColor(dLightColor);
            lightGoMat->SetColor(dLightColor);
        }

        GameObject *backpackModel = engine->CreateGameObject("Backpack");
        s->AddGameObject(backpackModel);
        ModelComponent *modelCmp = backpackModel->AddComponent<ModelComponent>();
        modelCmp->Init("./assets/models/backpack/backpack.obj");
        // modelCmp->Init("./assets/models/obj/Wolf_obj.obj");
        TransformComponent *backpackTf = backpackModel->GetComponent<TransformComponent *>();
        glm::mat4 backpackModelMat{1.f};
        backpackTf->Translate(glm::vec3(0.f, 0.f, -1.f));
        backpackTf->SetLocalScale(glm::vec3(0.5f));

        GameObject *plane = GameObjectFactory::CreatePlaneMeshGO(engine);
        s->AddGameObject(plane);
        // GameObject *outlinedCube = GameObjectFactory::CreateCubeMeshGO(engine);
        GameObject *cube2 = GameObjectFactory::CreateCubeMeshGO(engine);
        s->AddGameObject(cube2);
        GameObject *sphere1 = GameObjectFactory::CreateSphereMeshGO(engine);
        s->AddGameObject(sphere1);
        sphere1->Rename("sphere");

        TransformComponent *cube2Tf{cube2->GetComponent<TransformComponent *>()};
        cube2Tf->Translate(glm::vec3(2.f, 0.f, 0.f));

        TransformComponent* planeTf{plane->GetComponent<TransformComponent*>()};
        planeTf->Translate(glm::vec3{0.0f, -2.f, .0f});
        planeTf->RotateAroundAxis(glm::vec3{1.f, .0f, .0f},90.0f);
        planeTf->SetLocalScale(glm::vec3{10.f});

        TransformComponent* sphere1Tf{sphere1->GetComponent<TransformComponent*>()};
        sphere1Tf->Translate(glm::vec3{1.f, 1.f, -2.f});

        PhongModelMaterial *cube2Mat = engine->CreateMaterial<PhongModelMaterial>();
        cube2Mat->SetBaseColor(1.f, .5f, .91f);
        cube2->GetComponent<MeshComponent *>()->SetMaterial(cube2Mat);

        sphere1->GetComponent<MeshComponent *>()->SetMaterial(engine->CreateMaterial<DepthVisualizerMaterial>());

        SpotLightComponent *flashLight = CameraComponent::Main()->gameObject->AddComponent<SpotLightComponent>();
        flashLight->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong));
        flashLight->SetColor(glm::vec3(1.f));
        s->AddSpotLight();
        return s;
    }

    Scene *SceneMaker::MakeBlendingScene(FurryWolfEngine *engine) {
        std::vector<glm::vec3> vegetation;
        vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
        vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
        vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
        vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
        vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

        Scene *s = new Scene(engine);
        glm::mat4 model{1.0f};
        for (size_t i{0}; i < vegetation.size(); ++i) {
            GameObject *plane = GameObjectFactory::CreatePlaneMeshGO(engine);
            TransformComponent* planeTf{plane->GetComponent<TransformComponent*>()};
            planeTf->Translate(vegetation[i]);

            TextureLoadConfig tConfig;
            tConfig.clapMode = GL_CLAMP_TO_EDGE;
            SimpleUnlitMaterial *mat = engine->CreateMaterial<SimpleUnlitMaterial>();
            mat->AddAlbedoMap(
                ResourceManager::Instance()->LoadTexture<Texture>(
                    "./assets/images/textures/blending_transparent_window.png", tConfig));
            mat->SetOpaque(false);
            mat->SetTransparency(0.5f);

            plane->GetComponent<MeshComponent *>()->SetMaterial(mat);

            s->AddGameObject(plane);
        }
        return s;
    }

    glm::vec3 SceneMaker::cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };
}
