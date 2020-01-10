#include "SandboxApp.h"

#include <iostream>

SandboxApp::SandboxApp()
	: Application(1600, 900, false)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.1f, 1.0f);

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
	Renderer::SetClearColor(0.15f, 0.15f, 0.15f);
	Renderer::Clear();

	Scene scene;
	scene.SetCamera(m_Camera);
	scene.SetLightning(LightMode::FLAT_COLOR);

	
}
