#pragma once

#include "../renderer/VertexBuffer.h"
#include "../renderer/IndexBuffer.h"
#include "../renderer/VertexArray.h"
#include "../renderer/Texture.h"
#include "../renderer/Shader.h"

#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh
{
private:
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;

private:
	void SetupMesh();

public:

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	~Mesh();

	void Draw(std::shared_ptr<Shader> shader);
};