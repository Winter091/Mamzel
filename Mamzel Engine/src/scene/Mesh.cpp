#include "Mesh.h"

#include "../util/ErrorHandling.h"
#include "../renderer/RenderData.h"

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
	if (m_Textures.size() == 0)
	{
		shader->SetUniform("u_UseDiffuseTexture", 0);
		shader->SetUniform("u_UseSpecularTexture", 0);
	}
	else
	{
		shader->SetUniform("u_UseDiffuseTexture", 1);
		shader->SetUniform("u_UseSpecularTexture", 1);
		
		unsigned int diffuseNum = 0, specularNum = 0;

		for (int i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i].Bind(i);

			const std::string& name = m_Textures[i].GetName();

			if (name == "texture_diffuse")
				shader->SetUniform("u_DiffuseTextureSampler", i);
			else if (name == "texture_specular")
				shader->SetUniform("u_SpecularTextureSampler", i);
		}
	}
	
	m_VertexArray->Bind();
	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, nullptr));
}
