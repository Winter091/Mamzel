#pragma once

#include <glm/glm.hpp>

#include "buffers/VertexBuffer.h"
#include "buffers/VertexBufferLayout.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "../scene/Scene.h"
#include "../scene/Model.h"

class Renderer
{
private:
	static std::shared_ptr<Scene> s_Scene;
	static std::shared_ptr<Shader> s_CurrShader;

private:
	static void BindPhongLightningShader();
	static void SendMatrixAndTexture(const glm::mat4& transform, const glm::vec4& color, bool useTexture = false, float textureScale = 1.0f);

public:
	Renderer() = delete;

	static void BeginScene(const Scene& scene);
	static void EndScene();

	static void DrawCoordinateLines();

	static void DrawUserData(std::shared_ptr<VertexArray>& va, std::shared_ptr<Shader>& shader, const glm::mat4& modelMatrix);
	static void DrawUserData(std::shared_ptr<VertexArray>& va, std::shared_ptr<Shader>& shader, std::shared_ptr<Texture>& texture, const glm::mat4& modelMatrix);

	static void DrawModel(std::shared_ptr<Model>& model, const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), const glm::vec3 scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawModel(std::shared_ptr<Model>& model, const glm::mat4& transform = glm::mat4(1.0f));

	static void DrawTriangle(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawTriangle(const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawTriangle(std::shared_ptr<Texture>& texture, const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawTriangle(std::shared_ptr<Texture>& texture, const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));

	static void DrawQuad(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawQuad(const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawQuad(std::shared_ptr<Texture>& texture, const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawQuad(std::shared_ptr<Texture>& texture, const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));

	static void DrawCube(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawCube(const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawCube(std::shared_ptr<Texture>& texture, const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));
	static void DrawCube(std::shared_ptr<Texture>& texture, const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));
};