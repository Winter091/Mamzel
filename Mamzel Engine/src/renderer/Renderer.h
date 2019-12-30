#pragma once

#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "../core/Scene.h"

struct rendererData_t
{
	std::shared_ptr<VertexBuffer> triangleVB;
	std::shared_ptr<IndexBuffer> triangleIB;
	std::shared_ptr<VertexArray> triangleVA;

	std::shared_ptr<VertexBuffer> quadVB;
	std::shared_ptr<IndexBuffer> quadIB;
	std::shared_ptr<VertexArray> quadVA;

	std::shared_ptr<VertexBuffer> cubeVB;
	std::shared_ptr<VertexArray> cubeVA;

	std::shared_ptr<Shader> flatColorShader;
	std::shared_ptr<Shader> phongLightningShader;
};

class Renderer
{
private:
	std::shared_ptr<Scene> m_Scene;
	
	static rendererData_t s_RenderData;

private:
	void BindFlatColorShader(const glm::mat4& transform, const glm::vec4& color, bool useTexture, float textureRepeatCount);
	void BindPhongLightningShader(const glm::mat4& transform, const glm::vec4& color, bool useTexture, float textureRepeatCount);

public:

	Renderer();
	~Renderer();

	void BeginScene(const Scene& scene);
	void EndScene();

	void SetClearColor(float r, float g, float b) const;
	void Clear();

	void DrawCustomShape(const std::unique_ptr<VertexArray>& va, const std::unique_ptr<Shader>& shader, const glm::mat4& modelMatrix);
	void DrawCustomShape(const std::unique_ptr<VertexArray>& va, const std::unique_ptr<Shader>& shader, const std::shared_ptr<Texture> texture, const glm::mat4& modelMatrix);

	void DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	void DrawTriangle(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
	void DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));
	void DrawTriangle(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));

	void DrawQuad(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	void DrawQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
	void DrawQuad(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));
	void DrawQuad(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));

	void DrawCube(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	void DrawCube(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
	void DrawCube(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));
	void DrawCube(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));

};