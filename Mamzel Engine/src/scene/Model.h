#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName);

public:
	Model() = delete;
	Model(const char* path);
	~Model();

	void Draw(std::shared_ptr<Shader>& shader);
};