#pragma once
#include <vector>
#include <string>

#include "assimp/scene.h"

#include "engine/components/meshes/MeshComponent.h"
#include "engine/render/meshes/IndexedDrawMesh.h"
#include "engine/render/Texture.h"

#include "engine/render/materials/PhongModelMaterial.h"
namespace WEngine
{
  class ModelComponent : public MeshComponent
  {
  private:
    std::vector<IndexedDrawMesh *> meshes;
    PhongModelMaterial *phongMat;
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
    IndexedDrawMesh *processMesh(aiMesh *mesh, const aiScene *scene);
    /**
     * @brief Parse assimp's aiMesh object into our custom defined mesh object for OpenGL to render
     *
     * @param mat
     * @param type
     * @param typeName
     * @return std::vector<Texture>
     */
    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    virtual void Render() override;

  public:
    ModelComponent();
    virtual ~ModelComponent();
    void Init(std::string modelPath);
    virtual void DrawMeshOnly() override;
  };
}
