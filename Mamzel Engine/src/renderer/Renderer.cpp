#include "Renderer.h"
#include "../util/ErrorHandling.h"

#include <memory>

// Static variables init
rendererData_t Renderer::s_RenderData;
std::shared_ptr<Scene> Renderer::s_Scene;

void Renderer::BindFlatColorShader(const glm::mat4& transform, const glm::vec4& color, bool useTexture, float textureScale)
{
	s_RenderData.flatColorShader->Bind();
	s_RenderData.flatColorShader->SetUniform("u_MatrixMVP", s_Scene->GetCamera()->GetMatrixVP() * transform);
	s_RenderData.flatColorShader->SetUniform("u_Color", color.x, color.y, color.z, color.w);

	s_RenderData.flatColorShader->SetUniform("u_TextureRepeatCount", textureScale);
	s_RenderData.flatColorShader->SetUniform("u_UseTexture", (int)useTexture);
	s_RenderData.flatColorShader->SetUniform("u_TexureSampler", 0);
}

void Renderer::BindPhongLightningShader(const glm::mat4& transform, const glm::vec4& color, bool useTexture, float textureScale)
{
	s_RenderData.phongLightningShader->Bind();

	s_RenderData.phongLightningShader->SetUniform("u_MatrixMVP", s_Scene->GetCamera()->GetMatrixVP() * transform);
	s_RenderData.phongLightningShader->SetUniform("u_ObjectTransform", transform);

	s_RenderData.phongLightningShader->SetUniform("u_ObjectColor", color.x, color.y, color.z);
	s_RenderData.phongLightningShader->SetUniform("u_LightColor", 1.0f, 1.0f, 1.0f);

	s_RenderData.phongLightningShader->SetUniform("u_AmbientStrength", 0.1f);
	s_RenderData.phongLightningShader->SetUniform("u_DiffuseStrength", 1.0f);
	s_RenderData.phongLightningShader->SetUniform("u_SpecularStrength", 0.5f);

	s_RenderData.phongLightningShader->SetUniform("u_CameraPos", s_Scene->GetCamera()->GetPosition());
	s_RenderData.phongLightningShader->SetUniform("u_LightCount", (int)s_Scene->GetLightSources().size());
	for (int i = 0; i < s_Scene->GetLightSources().size(); i++)
	{
		std::string name = "u_LightPositions[" + std::to_string(i) + "]";
		s_RenderData.phongLightningShader->SetUniform(name.c_str(), s_Scene->GetLightSources()[i]);
	}

	s_RenderData.phongLightningShader->SetUniform("u_TextureRepeatCount", textureScale);
	s_RenderData.phongLightningShader->SetUniform("u_UseTexture", (int)useTexture);
	s_RenderData.phongLightningShader->SetUniform("u_TextureSampler", 0);
}

void Renderer::Init()
{
	s_RenderData.flatColorShader = std::make_shared<Shader>("res/shaders/flatColorShader.vert", "res/shaders/flatColorShader.frag");
	s_RenderData.phongLightningShader = std::make_shared<Shader>("res/shaders/phongLightning.vert", "res/shaders/phongLightning.frag");

	// Triangle data ================================================================================================
	float verticesTriangle[] = {
		// a_Position           a_TexCoord     a_Normal
		-0.5f, -0.5f,  0.0f,    0.0f, 0.0f,    0.0f,  0.0f,  1.0f,
		 0.0f,  0.5f,  0.0f,    0.5f, 1.0f,    0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,    1.0f, 0.0f,    0.0f,  0.0f,  1.0f,
	};
	unsigned int indicesTriangle[] = { 0, 1, 2 };

	s_RenderData.triangleVB = std::make_shared<VertexBuffer>(verticesTriangle, sizeof(verticesTriangle));
	s_RenderData.triangleIB = std::make_shared<IndexBuffer>(indicesTriangle, sizeof(indicesTriangle));
	VertexBufferLayout layoutTriangle = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_TexCoord" },
		{ GL_FLOAT, 3, "a_Normal" }
	};
	s_RenderData.triangleVA = std::make_shared<VertexArray>(s_RenderData.triangleVB, s_RenderData.triangleIB, layoutTriangle);

	// Quad data ====================================================================================================
	float verticesQuad[] = {
		// a_Position            a_TexCoord	     a_Normal
		-0.5f, -0.5f,  0.0f,     0.0f, 0.0f,     0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.0f,     0.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.0f,     1.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,     1.0f, 0.0f,     0.0f,  0.0f,  1.0f
	};
	unsigned int indicesQuad[] = { 0, 1, 2, 2, 3, 0 };

	s_RenderData.quadVB = std::make_shared<VertexBuffer>(verticesQuad, sizeof(verticesQuad));
	s_RenderData.quadIB = std::make_shared<IndexBuffer>(indicesQuad, sizeof(indicesQuad));
	VertexBufferLayout layoutQuad = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_TexCoord" },
		{ GL_FLOAT, 3, "a_Normal" }
	};
	s_RenderData.quadVA = std::make_shared<VertexArray>(s_RenderData.quadVB, s_RenderData.quadIB, layoutQuad);

	// Cube data ====================================================================================================
	float verticesCube[] = {
		// a_Position            a_TexCoord		 a_Normal
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,     0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,     0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,     0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,     0.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,     1.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f,     0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,     0.0f, 0.0f,     0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     0.0f,  1.0f,  0.0f
	};

	s_RenderData.cubeVB = std::make_shared<VertexBuffer>(verticesCube, sizeof(verticesCube));
	VertexBufferLayout layoutCube = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_TexCoord" },
		{ GL_FLOAT, 3, "a_Normal" }
	};
	s_RenderData.cubeVA = std::make_shared<VertexArray>(s_RenderData.cubeVB, layoutCube);
}

void Renderer::Free()
{
	s_RenderData.triangleVB = nullptr;
	s_RenderData.triangleIB = nullptr;
	s_RenderData.triangleVA = nullptr;

	s_RenderData.quadVB = nullptr;
	s_RenderData.quadIB = nullptr;
	s_RenderData.quadVA = nullptr;

	s_RenderData.cubeVB = nullptr;
	s_RenderData.cubeVA = nullptr;

	s_RenderData.flatColorShader = nullptr;
	s_RenderData.phongLightningShader = nullptr;
}

void Renderer::BeginScene(const Scene& scene)
{
	s_Scene = std::make_shared<Scene>(scene);
}

void Renderer::EndScene()
{
}

void Renderer::SetClearColor(float r, float g, float b)
{
	HANDLE_ERROR(glClearColor(r, g, b, 1.0f));
}

void Renderer::Clear()
{
	HANDLE_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawCustomShape(const std::unique_ptr<VertexArray>& va, const std::unique_ptr<Shader>& shader, const glm::mat4& modelMatrix)
{
	va->Bind();
	shader->Bind();

	shader->SetUniform("u_MatrixMVP", s_Scene->GetCamera()->GetMatrixVP() * modelMatrix);

	// No IndexBuffer is used
	if (va->GetIndexCount() == -1)
	{
		HANDLE_ERROR(glDrawArrays(GL_TRIANGLES, 0, va->GetVertexCount()));
	}
	// Use indexed draw call
	else
	{
		HANDLE_ERROR(glDrawElements(GL_TRIANGLES, va->GetIndexCount(), GL_UNSIGNED_INT, nullptr));
	}
}

void Renderer::DrawCustomShape(const std::unique_ptr<VertexArray>& va, const std::unique_ptr<Shader>& shader, const std::shared_ptr<Texture> texture, const glm::mat4& modelMatrix)
{
	texture->Bind();
	DrawCustomShape(va, shader, modelMatrix);
}

// Triangles =========================================================================================================================================

// Non-textured
void Renderer::DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const glm::vec4& color)
{
	DrawTriangle(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), color);
}

void Renderer::DrawTriangle(const glm::mat4& transform, const glm::vec4& color)
{		
	if (s_Scene->GetLightMode() == LightMode::FLAT_COLOR)
		BindFlatColorShader(transform, color, false, 0);
	else if (s_Scene->GetLightMode() == LightMode::PHONG_LIGHTNING)
		BindPhongLightningShader(transform, color, false, 0);
	
	s_RenderData.triangleVA->Bind();

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}

// Textured
void Renderer::DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color)
{
	DrawTriangle(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), texture, color);
}

void Renderer::DrawTriangle(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color)
{
	texture->Bind();

	if (s_Scene->GetLightMode() == LightMode::FLAT_COLOR)
		BindFlatColorShader(transform, color, true, texture->GetScale());
	else if (s_Scene->GetLightMode() == LightMode::PHONG_LIGHTNING)
		BindPhongLightningShader(transform, color, true, texture->GetScale());

	s_RenderData.triangleVA->Bind();

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}

// Quads =============================================================================================================================================

// Non-textured
void Renderer::DrawQuad(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const glm::vec4& color)
{
	DrawQuad(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), color);
}

void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	if (s_Scene->GetLightMode() == LightMode::FLAT_COLOR)
		BindFlatColorShader(transform, color, false, 0);
	else if (s_Scene->GetLightMode() == LightMode::PHONG_LIGHTNING)
		BindPhongLightningShader(transform, color, false, 0);

	s_RenderData.quadVA->Bind();

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

// Textured
void Renderer::DrawQuad(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color)
{
	DrawQuad(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), texture, color);
}

void Renderer::DrawQuad(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color)
{
	texture->Bind();
	
	if (s_Scene->GetLightMode() == LightMode::FLAT_COLOR)
		BindFlatColorShader(transform, color, true, texture->GetScale());
	else if (s_Scene->GetLightMode() == LightMode::PHONG_LIGHTNING)
		BindPhongLightningShader(transform, color, true, texture->GetScale());

	s_RenderData.quadVA->Bind();

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

// Cubes =============================================================================================================================================

// Non-textured
void Renderer::DrawCube(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const glm::vec4& color)
{
	DrawCube(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), color);
}

void Renderer::DrawCube(const glm::mat4& transform, const glm::vec4& color)
{
	if (s_Scene->GetLightMode() == LightMode::FLAT_COLOR)
		BindFlatColorShader(transform, color, false, 0);
	else if (s_Scene->GetLightMode() == LightMode::PHONG_LIGHTNING)
		BindPhongLightningShader(transform, color, false, 0);

	s_RenderData.cubeVA->Bind();

	HANDLE_ERROR(glDrawArrays(GL_TRIANGLES, 0, 36));
}

// Textured
void Renderer::DrawCube(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color)
{
	DrawCube(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), texture, color);
}

void Renderer::DrawCube(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color)
{
	texture->Bind();
	
	if (s_Scene->GetLightMode() == LightMode::FLAT_COLOR)
		BindFlatColorShader(transform, color, true, texture->GetScale());
	else if (s_Scene->GetLightMode() == LightMode::PHONG_LIGHTNING)
		BindPhongLightningShader(transform, color, true, texture->GetScale());

	s_RenderData.cubeVA->Bind();

	HANDLE_ERROR(glDrawArrays(GL_TRIANGLES, 0, 36));
}
