#pragma once
#include <vector>
#include <string>

#include "assimp/scene.h"

#include "engine/components/Component.h"
#include "engine/components/IndexedDrawMeshComponent.h"
#include "engine/render/Texture.h"
namespace WEngine
{
  class ModelComponent : public Component
  {
  private:
    std::vector<IndexedDrawMeshComponent *> meshes;
    // the directory to load textures
    std::string directory;

    void loadModel(std::string path);
    /**
     * @brief This is a recursive function, since the aiNode is a recursive structure.
     *
     * @param node
     * @param scene
     */
    void processNode(aiNode *node, const aiScene *scene);
    IndexedDrawMeshComponent *processMesh(aiMesh *mesh, const aiScene *scene);
    /**
     * @brief Parse assimp's aiMesh object into our custom defined mesh object for OpenGL to render
     *
     * @param mat
     * @param type
     * @param typeName
     * @return std::vector<Texture>
     */
    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    virtual void Update(float deltaTime) override;

  public:
    ModelComponent();
    ~ModelComponent();
    void Init(std::string modelPath);
  };
}
