#include <string>
#include <iostream>
#include <memory>

#include "engine/math/glm/glm.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "engine/core/FurryWolfEngine.h"
#include "engine/core/GameObject.h"
#include "engine/core/ResourceManager.h"
#include "engine/components/meshes/ModelComponent.h"
#include "engine/render/meshes/IndexedDrawMesh.h"

#include "engine/render/materials/PhongModelMaterial.h"

namespace WEngine
{
  ModelComponent::ModelComponent()
  {
    meshes = std::vector<IndexedDrawMesh *>();
    directory = std::string();
  }
  ModelComponent::~ModelComponent() {}

  void ModelComponent::Init(std::string modelPath)
  {
    loadModel(modelPath);
  }

  void ModelComponent::loadModel(std::string path)
  {
    // import the model into assimp's Scene object
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::cout << "Error importing model: " << importer.GetErrorString() << std::endl;
      return;
    }

    // the directory for the texture presumably at the same directory of the model
    directory = path.substr(0, path.find_last_of('/'));
    // parse data in the Scene object and create a list of mesh objects from it
    processNode(scene->mRootNode, scene);
  }

  void ModelComponent::processNode(aiNode *node, const aiScene *scene)
  {
    // build mesh for current node
    for (size_t i{0}; i < node->mNumMeshes; ++i)
    {
      // accessing the mesh indices from the root node based on current node
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(processMesh(mesh, scene));
    }
    // recursively build mesh for child node
    for (size_t i{0}; i < node->mNumChildren; ++i)
    {
      processNode(node->mChildren[i], scene);
    }
  }

  IndexedDrawMesh *ModelComponent::processMesh(aiMesh *mesh, const aiScene *scene)
  {
    IndexedDrawMesh *indMesh = new IndexedDrawMesh();
    std::vector<Vertex> vertices{};
    std::vector<unsigned int> indices{};

    for (size_t i{0}; i < mesh->mNumVertices; ++i)
    {
      Vertex vertex;

      // position
      aiVector3D assimpV = mesh->mVertices[i];
      vertex.Position = glm::vec3(assimpV.x, assimpV.y, assimpV.z);

      // normal
      aiVector3D assimpN = mesh->mNormals[i];
      vertex.Normal = glm::vec3(assimpN.x, assimpN.y, assimpN.z);

      // texture coord
      if (mesh->mTextureCoords[0])
      {
        // first texture at current vertex
        vertex.TexCoords = glm::vec2(
            mesh->mTextureCoords[0][i].x,
            mesh->mTextureCoords[0][i].y);
      }
      vertices.push_back(vertex);
    }

    // for indices, we loot through each face, and its indices
    for (size_t i{0}; i < mesh->mNumFaces; ++i)
    {
      aiFace face = mesh->mFaces[i];
      for (size_t j{0}; j < face.mNumIndices; ++j)
      {
        indices.push_back(face.mIndices[j]);
      }
    }
    indMesh->Init(vertices, indices);

    PhongModelMaterial *mat = engine->CreateMaterial<PhongModelMaterial>();
    // material/textures
    if (mesh->mMaterialIndex >= 0)
    {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
      // albedo map
      std::vector<std::shared_ptr<Texture>> albedos = loadMaterialTextures(material, aiTextureType_DIFFUSE);
      // specular map
      std::vector<std::shared_ptr<Texture>> speculars = loadMaterialTextures(material, aiTextureType_SPECULAR);
      for (size_t i{0}; i < albedos.size(); ++i)
      {
        mat->AddAlbedoMap(albedos[i]);
      }
      for (size_t i{0}; i < speculars.size(); ++i)
      {
        mat->AddSpecularMap(speculars[i]);
      }
    }

    phongMat = mat;
    return indMesh;
  }

  std::vector<std::shared_ptr<Texture>> ModelComponent::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
  {
    std::vector<std::shared_ptr<Texture>> textures{};
    for (size_t i{0}; i < mat->GetTextureCount(type); ++i)
    {
      aiString ais;
      mat->GetTexture(type, i, &ais);
      std::string texturePath = std::string(ais.C_Str());
      texturePath = texturePath.substr(texturePath.find_last_of('\\') + 1);

      const std::shared_ptr<Texture> texture = ResourceManager::Instance()->LoadTexture(directory + "/" + texturePath);
      if (texture)
      {
        textures.push_back(texture);
      }
    }
    return textures;
  }

  void ModelComponent::Render(bool transparentPass)
  {
    phongMat->Use(gameObject);
    DrawMeshOnly();
  }
  void ModelComponent::DrawMeshOnly()
  {
    for (size_t i{0}; i < meshes.size(); ++i)
    {
      meshes[i]->Draw();
    }
  }
}
