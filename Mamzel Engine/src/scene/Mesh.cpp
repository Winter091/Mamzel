#include "Mesh.h"
#include "../util/ErrorHandling.h"

void Mesh::SetupMesh()
{
	m_VertexBuffer = VertexBuffer::Create(m_Vertices.data(), (unsigned int)m_Vertices.size() * sizeof(Vertex));
	m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), (unsigned int)m_Indices.size() * sizeof(unsigned int));
	VertexBufferLayout layout = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_TexCoord" },
		{ GL_FLOAT, 3, "a_Normal" }
	};
	m_VertexArray = VertexArray::Create(m_VertexBuffer, m_IndexBuffer, layout);
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Textures = textures;

	SetupMesh();
}

Mesh::~Mesh()
{
	m_VertexBuffer = nullptr;
	m_IndexBuffer = nullptr;
	m_VertexArray = nullptr;

	m_Vertices.clear();
	m_Indices.clear();
	m_Textures.clear();
}

void Mesh::Draw(std::shared_ptr<Shader>& shader)
{
	unsigned int diffuseNum = 0, specularNum = 0;

	for (int i = 0; i < m_Textures.size(); i++)
	{
		const std::string& name = m_Textures[i].GetName();

		std::string num;
		if (name == "texture_diffuse")
			num = std::to_string(diffuseNum++);
		else if (name == "texture_specular")
			num = std::to_string(specularNum++);

		m_Textures[i].Bind(i);
		shader->SetUniform((name + num).c_str(), i);
	}

	m_VertexArray->Bind();
	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, nullptr));
}
