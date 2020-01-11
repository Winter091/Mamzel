#include "Renderer.h"

#include "../util/ErrorHandling.h"
#include "RenderData.h"

#include <memory>

// Static variables init
std::shared_ptr<Scene> Renderer::s_Scene;
std::shared_ptr<Shader> Renderer::s_CurrShader;


void Renderer::BindPhongLightningShader()
{
	RenderData::phongLightningShader->Bind();

	RenderData::phongLightningShader->SetUniform("u_CameraPos", s_Scene->GetCamera()->GetPosition());

	int useBlinn = (s_Scene->GetLightMode() == LightMode::BLINN_PHONG_LIGHTNING ? 1 : 0);
	RenderData::phongLightningShader->SetUniform("u_UseBlinn", useBlinn);

	// Global light
	const std::shared_ptr<DirectionalLight>& directionalLight = s_Scene->GetDirectionalLight();
	if (directionalLight)
	{
		RenderData::phongLightningShader->SetUniform("u_UseDirectionalLight", 1);

		RenderData::phongLightningShader->SetUniform("u_DirectionalLight.direction", directionalLight->GetDirection());
		RenderData::phongLightningShader->SetUniform("u_DirectionalLight.diffuseColor", directionalLight->GetDiffuseColor());
		RenderData::phongLightningShader->SetUniform("u_DirectionalLight.specularColor", directionalLight->GetSpecularColor());
		RenderData::phongLightningShader->SetUniform("u_DirectionalLight.intensity", directionalLight->GetIntensity());
	}

	// Point Lights
	RenderData::phongLightningShader->SetUniform("u_PointLight.ambient", 0.0f);
	RenderData::phongLightningShader->SetUniform("u_PointLight.diffuse", 1.0f);
	RenderData::phongLightningShader->SetUniform("u_PointLight.specular", 0.5f);

	RenderData::phongLightningShader->SetUniform("u_PointLight.count", (int)s_Scene->GetPointLights().size());

	const std::vector<std::shared_ptr<PointLight>>& pointLights = s_Scene->GetPointLights();
	for (int i = 0; i < s_Scene->GetPointLights().size(); i++)
	{
		std::shared_ptr<PointLight> light = pointLights[i];
		std::string index = std::to_string(i);
		const glm::vec3& lightAttenuation = light->GetAttenuation();

		std::string name = "u_PointLight.positions[" + index + "]";
		RenderData::phongLightningShader->SetUniform(name.c_str(), light->GetPosition());

		name = "u_PointLight.diffuseColor[" + index + "]";
		RenderData::phongLightningShader->SetUniform(name.c_str(), light->GetDiffuseColor());

		name = "u_PointLight.specularColor[" + index + "]";
		RenderData::phongLightningShader->SetUniform(name.c_str(), light->GetSpecularColor());

		name = "u_PointLight.constant[" + index + "]";
		RenderData::phongLightningShader->SetUniform(name.c_str(), lightAttenuation.x);

		name = "u_PointLight.linear[" + index + "]";
		RenderData::phongLightningShader->SetUniform(name.c_str(), lightAttenuation.y);

		name = "u_PointLight.quadratic[" + index + "]";
		RenderData::phongLightningShader->SetUniform(name.c_str(), lightAttenuation.z);
	}
}

void Renderer::SendMatrixAndTexture(const glm::mat4& transform, const glm::vec4& color, bool useTexture, float textureScale)
{
	s_CurrShader->Bind();

	if (s_Scene->GetLightMode() != LightMode::FLAT_COLOR)
		s_CurrShader->SetUniform("u_ObjectTransform", transform);

	s_CurrShader->SetUniform("u_MatrixMVP", s_Scene->GetCamera()->GetMatrixVP() * transform);

	s_CurrShader->SetUniform("u_ObjectColor", color.x, color.y, color.z, color.w);

	if (useTexture)
	{
		s_CurrShader->SetUniform("u_UseTexture", (int)useTexture);
		s_CurrShader->SetUniform("u_TextureScale", textureScale);
		s_CurrShader->SetUniform("u_TextureSampler", 0);
	}
}

void Renderer::BeginScene(const Scene& scene)
{
	s_Scene = std::make_shared<Scene>(scene);

	LightMode light = s_Scene->GetLightMode();

	if (light == LightMode::FLAT_COLOR)
	{
		s_CurrShader = RenderData::flatColorShader;
	}
	else if (light == LightMode::PHONG_LIGHTNING)
	{
		s_CurrShader = RenderData::phongLightningShader;
		BindPhongLightningShader();
	}
	else if (light == LightMode::BLINN_PHONG_LIGHTNING)
	{
		s_CurrShader = RenderData::phongLightningShader;
		BindPhongLightningShader();
	}
}

void Renderer::EndScene()
{
	s_Scene = nullptr;
	s_CurrShader = nullptr;
}

void Renderer::DrawCoordinateLines()
{
	RenderData::linesVA->Bind();
	RenderData::flatColorShader->Bind();

	glm::mat4 model =glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));

	RenderData::flatColorShader->SetUniform("u_MatrixMVP", s_Scene->GetCamera()->GetMatrixVP() * model);
	RenderData::flatColorShader->SetUniform("u_UseTexture", (int)0);

	RenderData::flatColorShader->SetUniform("u_ObjectColor", glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));
	HANDLE_ERROR(glDrawArrays(GL_LINES, 0, 2));

	RenderData::flatColorShader->SetUniform("u_ObjectColor", glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	HANDLE_ERROR(glDrawArrays(GL_LINES, 2, 2));

	RenderData::flatColorShader->SetUniform("u_ObjectColor", glm::vec4(0.0f, 0.0f, 1.0f, 0.5f));
	HANDLE_ERROR(glDrawArrays(GL_LINES, 4, 2));
}

void Renderer::DrawUserData(std::shared_ptr<VertexArray>& va, std::shared_ptr<Shader>& shader, const glm::mat4& modelMatrix)
{
	va->Bind();
	shader->Bind();

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

void Renderer::DrawUserData(std::shared_ptr<VertexArray>& va, std::shared_ptr<Shader>& shader, std::shared_ptr<Texture>& texture, const glm::mat4& modelMatrix)
{
	texture->Bind();
	DrawUserData(va, shader, modelMatrix);
}

// Triangles =========================================================================================================================================

// Non-textured
void Renderer::DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, const glm::vec4& color)
{
	DrawTriangle(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), color);
}

void Renderer::DrawTriangle(const glm::mat4& transform, const glm::vec4& color)
{		
	SendMatrixAndTexture(transform, color);
	RenderData::triangleVA->Bind();

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}

// Textured
void Renderer::DrawTriangle(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, std::shared_ptr<Texture>& texture, const glm::vec4& color)
{
	DrawTriangle(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), texture, color);
}

void Renderer::DrawTriangle(const glm::mat4& transform, std::shared_ptr<Texture>& texture, const glm::vec4& color)
{
	texture->Bind();
	SendMatrixAndTexture(transform, color, true, texture->GetScale());
	RenderData::triangleVA->Bind();

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
	SendMatrixAndTexture(transform, color);

	RenderData::quadVA->Bind();

	HANDLE_ERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

// Textured
void Renderer::DrawQuad(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, std::shared_ptr<Texture>& texture, const glm::vec4& color)
{
	DrawQuad(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), texture, color);
}

void Renderer::DrawQuad(const glm::mat4& transform, std::shared_ptr<Texture>& texture, const glm::vec4& color)
{
	texture->Bind();
	SendMatrixAndTexture(transform, color, true, texture->GetScale());
	RenderData::quadVA->Bind();

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
	SendMatrixAndTexture(transform, color);
	RenderData::cubeVA->Bind();

	HANDLE_ERROR(glDrawArrays(GL_TRIANGLES, 0, 36));
}

// Textured
void Renderer::DrawCube(const glm::vec3& position, const glm::vec4& rotation, const glm::vec3& scale, std::shared_ptr<Texture>& texture, const glm::vec4& color)
{
	DrawCube(glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z)) * glm::scale(glm::mat4(1.0), scale), texture, color);
}

void Renderer::DrawCube(const glm::mat4& transform, std::shared_ptr<Texture>& texture, const glm::vec4& color)
{
	texture->Bind();
	SendMatrixAndTexture(transform, color, true, texture->GetScale());
	RenderData::cubeVA->Bind();

	HANDLE_ERROR(glDrawArrays(GL_TRIANGLES, 0, 36));
}
