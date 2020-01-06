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
	static std::shared_ptr<Scene> s_Scene;
	static rendererData_t s_RenderData;

private:
	static void BindFlatColorShader(const glm::mat4& transform, const glm::vec4& color, bool useTexture, float textureScale);
	static void BindPhongLightningShader(const glm::mat4& transform, const glm::vec4& color, bool useTexture, float textureScale, bool useBlinn);

public:

	Renderer() = delete;

	static void Init();
	static void Free();

	static void BeginScene(const Scene& scene);
	static void EndScene();

	static void SetClearColor(float r, float g, float b);
	static void Clear();

	static void DrawCustomShape(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<Shader>& shader, const glm::mat4& modelMatrix);
	static void DrawCustomShape(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture> texture, const glm::mat4& modelMatrix);

	static void DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawTriangle(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
	static void DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));
	static void DrawTriangle(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));

	static void DrawQuad(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
	static void DrawQuad(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));
	static void DrawQuad(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));

	static void DrawCube(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawCube(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
	static void DrawCube(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));
	static void DrawCube(const glm::mat4& transform, std::shared_ptr<Texture> texture, const glm::vec4& color = glm::vec4(1.0f));

};