#include "SandboxApp.h"

#include <iostream>

SandboxApp::SandboxApp()
	: Application(1600, 900, false)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 2.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.008f, 0.08f);

	m_Model = std::make_shared<Model>("res/models/lowpolywolf/wolf.obj");
	m_Shader = Shader::Create("res/shaders/modelShader.glsl");

	TextureLibrary::Load("redstone_lamp", "res/textures/redstone_lamp.png");
	TextureLibrary::SetWrapAndFilterMode("redstone_lamp", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
}

SandboxApp::~SandboxApp()
{
	m_Model = nullptr;
	m_Shader = nullptr;
}

void SandboxApp::DrawGui()
{
	ImGui::Begin("Gui");
	ImGui::Text("Frame takes %.3f ms. (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat3("Position1", &m_Lamp1Pos.x, -15.0f, 15.0f);
	ImGui::End();
}

void SandboxApp::DrawOpenGL()
{
	RenderCommand::SetClearColor(0.15f, 0.15f, 0.15f);
	RenderCommand::Clear();

	PointLight lamp1(m_Lamp1Pos, 200.0f);

	Scene scene;
	scene.SetCamera(m_Camera);
	scene.AddPointLight(lamp1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Renderer::BeginScene(scene);
	{
		Renderer::DrawCoordinateLines();

		Renderer::DrawCube(m_Lamp1Pos, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("redstone_lamp"));

		m_Shader->Bind();
		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.01f));
		m_Shader->SetUniform("u_MatrixMVP", m_Camera->GetMatrixVP() * transform);
		m_Shader->SetUniform("u_ObjectTransform", transform);

		m_Shader->SetUniform("u_Light.position", m_Lamp1Pos);
		m_Shader->SetUniform("u_Light.ambient", 0.1f);
		m_Shader->SetUniform("u_Light.diffuse", 1.0f);
		m_Shader->SetUniform("u_Light.specular", 0.5f);
		m_Shader->SetUniform("u_Light.diffuseColor", glm::vec3(1.0f));
		m_Shader->SetUniform("u_Light.specularColor", glm::vec3(1.0f));
		m_Shader->SetUniform("u_CameraPos", m_Camera->GetPosition());

		m_Model->Draw(m_Shader);
	}
	Renderer::EndScene();


}
