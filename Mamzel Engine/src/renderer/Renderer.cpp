#include "Renderer.h"
#include "../util/ErrorHandling.h"

#include <memory>

// Static variable init
rendererData_t Renderer::s_RenderData;

Renderer::Renderer()
	:m_CameraMatrixVP(1.0f)
{

	s_RenderData.flatColorShader = std::make_unique<Shader>("res/shaders/flatColorShader.vert", "res/shaders/flatColorShader.frag");
	
	// Triangle data ================================================================================================
	float verticesTriangle[] = {
		-0.5f, -0.5f,  0.0f,
		 0.0f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f
	};
	unsigned int indicesTriangle[] = { 0, 1, 2 };

	s_RenderData.triangleVB = std::make_unique<VertexBuffer>(verticesTriangle, sizeof(verticesTriangle));
	s_RenderData.triangleIB = std::make_unique<IndexBuffer>(indicesTriangle, sizeof(indicesTriangle));
	VertexBufferLayout layoutTriangle = { { GL_FLOAT, 3, "a_Position" } };
	s_RenderData.triangleVA = std::make_unique<VertexArray>(s_RenderData.triangleVB, s_RenderData.triangleIB, layoutTriangle);
	
	// Quad data ====================================================================================================
	float verticesQuad[] = {
		-0.5f, -0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f
	};
	unsigned int indicesQuad[] = { 0, 1, 2, 2, 3, 0 };

	s_RenderData.quadVB = std::make_unique<VertexBuffer>(verticesQuad, sizeof(verticesQuad));
	s_RenderData.quadIB = std::make_unique<IndexBuffer>(indicesQuad, sizeof(indicesQuad));
	VertexBufferLayout layoutQuad = { { GL_FLOAT, 3, "a_Position" } };
	s_RenderData.quadVA = std::make_unique<VertexArray>(s_RenderData.quadVB, s_RenderData.quadIB, layoutQuad);
}

Renderer::~Renderer()
{
	s_RenderData.triangleVB = nullptr;
	s_RenderData.triangleIB = nullptr;
	s_RenderData.triangleVA = nullptr;
	s_RenderData.quadVB = nullptr;
	s_RenderData.quadIB = nullptr;
	s_RenderData.quadVA = nullptr;
	s_RenderData.flatColorShader = nullptr;
}

void Renderer::BeginScene(const glm::mat4& cameraMatrixMP)
{
	m_CameraMatrixVP = cameraMatrixMP;
}

void Renderer::EndScene()
{
}

void Renderer::SetClearColor(float r, float g, float b) const
{
	HANDLE_ERROR(glClearColor(r, g, b, 1.0f));
}

void Renderer::Clear()
{
	HANDLE_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawUserShape(const std::unique_ptr<VertexArray>& va, const std::unique_ptr<Shader>& shader, const glm::mat4& modelMatrix)
{
	va->Bind();
	shader->Bind();

	shader->setUniform("u_MatrixMVP", m_CameraMatrixVP * modelMatrix);

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, va->GetIndexCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawTriangle(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	DrawTriangle(glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), size), color);
}

void Renderer::DrawTriangle(const glm::mat4& transform, const glm::vec4& color)
{
	s_RenderData.triangleVA->Bind();
	s_RenderData.flatColorShader->Bind();
	s_RenderData.flatColorShader->setUniform("u_MatrixMVP", m_CameraMatrixVP * transform);
	s_RenderData.flatColorShader->setUniform("u_Color", color.x, color.y, color.z, color.w);

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	DrawQuad(glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), size), color);
}

void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	s_RenderData.quadVA->Bind();
	s_RenderData.flatColorShader->Bind();
	s_RenderData.flatColorShader->setUniform("u_MatrixMVP", m_CameraMatrixVP * transform);
	s_RenderData.flatColorShader->setUniform("u_Color", color.x, color.y, color.z, color.w);

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

