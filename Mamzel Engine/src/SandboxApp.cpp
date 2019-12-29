#include "SandboxApp.h"

SandboxApp::SandboxApp()
	: Application(1600, 900)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.05f, 0.8f);

	m_Renderer->SetClearColor(0.15f, 0.15f, 0.18f);
}

SandboxApp::~SandboxApp()
{
	
}

void SandboxApp::DrawGui()
{
	ImGui::Begin("Gui");
	ImGui::Text("Frame takes %.3f ms. (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void SandboxApp::DrawOpenGL()
{
	m_Renderer->Clear();

	static glm::vec3 lamp1Position = glm::vec3(2.0, 0.0, 2.0);
	static glm::vec3 lamp2Position = glm::vec3(-2.0, 0.0, -2.0);

	Scene scene;
	scene.SetCamera(m_Camera);
	scene.SetLightning(LightMode::PHONG_LIGHTNING);
	scene.AddLightSource(lamp1Position);
	scene.AddLightSource(lamp2Position);

	m_Renderer->BeginScene(scene);
	{
		glm::mat4 cubeMatrix = glm::rotate(glm::mat4(1.0), m_Time, glm::vec3(1.0));
		m_Renderer->DrawCube(cubeMatrix, { 0.2, 0.3, 0.8, 1.0 });
	}
	m_Renderer->EndScene();

	scene.SetLightning(LightMode::FLAT_COLOR);
	m_Renderer->BeginScene(scene);
	{
		m_Renderer->DrawCube(lamp1Position, { 1.0, 1.0, 1.0, 0.0 }, { 0.8, 0.8, 0.8 });
		m_Renderer->DrawCube(lamp2Position, { 1.0, 1.0, 1.0, 0.0 }, { 0.8, 0.8, 0.8 });
	}
	m_Renderer->EndScene();
}
