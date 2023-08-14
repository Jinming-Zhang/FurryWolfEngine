# Model Import
# Assimp
*assimp* is a model importing library, stands for Open Asset Import Library.

##### structure of assimp
![[assimpDataStructureDiagram.png]]

##### Scene Object
*Scene* object is the root object of *assimp*'s data interface. We can access all the data we need from the loaded model from the *Scene* object.

##### Node Object
Each *Node* object in *assimp* represent a single *Mehs*, and stores a list of mesh indices that consist of that mesh, as well as any child Node/Mesh objects of that Node.

The *Node* structure defines a parent-child relation between meshes,
## Steps to import model using assimp
Load the model into a data structure of *assimp* called a *Scene* object. We can also pass some post-processing options/flags to configure *assimp* on how to import the model.
```cpp
Assimp::Importer importer;
// post-processing options:
// 1. transform all the model's primitive shapes to triangles
// 2. 
const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
```

[List of available post processing options for assimp](https://assimp.sourceforge.net/lib_html/postprocess_8h.html)

Following are some useful post-processing options:
- `aiProcess_Triangulate`: transform all the model's primitive shapes to triangles
- `aiProcess_FlipUVs`: flips the texture coordinates on the y-axis when necessary
- `aiProcess_GenNormals`: creates normal vectors for each vertex if the model doesn't contain normal vectors.
- `aiProcess_SplitLargeMeshes`: splits large meshes into smaller sub-meshes.
- `aiProcess_OptimizeMeshes`: join meshes into one larger mesh, to help reducing drawing calls.


## Translate Scene object to Mesh object
After loaded the model into *assimp*'s *Scene* object, we need to initialize an array of *Mesh* objects from it.

To import all of the *scene* object's nodes, starting from the *mRootNode* member of the *scene* object.

Since each node contains a set of mesh indices where each index points to a specific mesh located in the *Scene* object, we will retrieve these mesh indices for each *Node*, process them one by one. Then repeat this for each of the child node.
#### Translate aiMesh to custom defined Mesh object
For our case, a *Mesh* object that uses indexed-draw to render require a list of **vertices** and a list of **indices**, so we will extract these two information from *aiMesh* object of *assimp*.

It will involve 3 steps for us to construct a *Mesh* object:
1. Retrieve all the vertex data
2. Retrieve all the indices data
3. Retrieve all the materials data

Vertex data in *aiMesh* is stored as *aiVector3D* object in its *mVertices*, *mNormals* member:
```cpp
Vertex vertex;
aiVector3D assimpV = mesh->mVertices[i];
vertex.Position = glm::vec3(assimpV.x, assimpV.y, assimpV.z);
```
For texture coordinate, since assimp allows a vertex to have up to 8 different texture coordinates, it's stored as an array. We only worry about the first one:
```cpp
if (mesh->mTextureCoords[0])
{
	// first texture at current vertex
	vertex.TexCoords = glm::vec2(
	mesh->mTextureCoords[0][i].x,
	mesh->mTextureCoords[0][i].y);
}
```

###### Face
*assimp* defines each *aiMesh* as having an array of *aiFace* objects, where each face represents a single primitive (doesn't have to be triangle, but since we configured the post-processing option of `aiProcess_Triangulate`, it will always be triangle).

A *aiFace* contains the indices of the vertices (from its *aiMesh*) that we need to draw in what order for its primitive.

#### Material
*aiMaterial* is the object that assimp used to store a material. For a model, assimp stores all it's material in the root *Scene* object, and each *aiMesh* will store the index of the material it uses in its *mMaterialIndex* member.


