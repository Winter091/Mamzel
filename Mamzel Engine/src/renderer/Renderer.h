#pragma once

#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

struct rendererData_t
{
	std::unique_ptr<VertexBuffer> triangleVB;
	std::unique_ptr<IndexBuffer> triangleIB;
	std::unique_ptr<VertexArray> triangleVA;

	std::unique_ptr<VertexBuffer> quadVB;
	std::unique_ptr<IndexBuffer> quadIB;
	std::unique_ptr<VertexArray> quadVA;

	std::unique_ptr<Shader> flatColorShader;
};

class Renderer
{
private:
	glm::mat4 m_CameraMatrixVP;
	static rendererData_t s_RenderData;

public:

	Renderer();
	~Renderer();

	void BeginScene(const glm::mat4& cameraMatrixMP);
	void EndScene();

	void SetClearColor(float r, float g, float b) const;
	void Clear();

	void DrawUserShape(const std::unique_ptr<VertexArray>& va, const std::unique_ptr<Shader>& shader, const glm::mat4& modelMatrix);

	void DrawTriangle(const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	void DrawTriangle(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));

	void DrawQuad(const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	void DrawQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
};