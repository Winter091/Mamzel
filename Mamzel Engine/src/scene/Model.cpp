#include "Model.h"

#include <iostream>


void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		std::shared_ptr<Mesh> processed = ProcessMesh(mesh, scene);
		m_Meshes.push_back(*processed);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		
		if (mesh->mNormals)
			vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		else
			vertex.normal = glm::vec3(0.0f);

		if (mesh->mTextureCoords[0])
			vertex.texCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		else
			vertex.texCoord = glm::vec2(0.0f);

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// If mesh has a material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps  = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return std::make_shared<Mesh>(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName)
{
	static std::vector<Texture> alreadyLoaded;

	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		std::string str2(str.C_Str());
		std::string path = m_Directory + str2;

		bool found = false;

		for (auto& texture : alreadyLoaded)
		{
			// Already loaded
			if (texture.GetPath() == path)
			{
				found = true;
				textures.push_back(texture);
				break;
			}
		}

		if (!found)
		{
			Texture texture(path.c_str(), typeName);
			textures.push_back(texture);
			alreadyLoaded.push_back(texture);
		}
	}

	return textures;
}

Model::Model(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene)
	{
		std::cout << "[Model] Error! Unable to open [" << path << "]\n";
		exit(0);
	}

	if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		std::cout << "[Model] Error! [" << path << "] data is incomplete\n";
		exit(0);
	}

	if (!scene->mRootNode)
	{
		std::cout << "[Model] Error! [" << path << "] RootNode is missing\n";
		exit(0);
	}

	std::string pathStr(path);
	m_Directory = pathStr.substr(0, pathStr.find_last_of('/') + 1);

	ProcessNode(scene->mRootNode, scene);
}

Model::~Model()
{
	m_Meshes.clear();
}

std::shared_ptr<Model> Model::Create(const char* path)
{
	return std::make_shared<Model>(path);
}

void Model::Draw(std::shared_ptr<Shader>& shader)
{
	for (auto& mesh : m_Meshes)
	{
		mesh.Draw(shader);
	}
}
