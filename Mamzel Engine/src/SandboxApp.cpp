#include "SandboxApp.h"

SandboxApp::SandboxApp()
	: Application(1600, 900)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.05f, 0.8f);

	m_Renderer->SetClearColor(0.15f, 0.15f, 0.18f);

	m_LampTexture = std::make_shared<Texture>("res/textures/redstone_lamp.png");
	m_LampTexture->SetWrapAndFilterMode(GL_REPEAT, GL_NEAREST);
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
	scene.AddLightSource(lamp1Position);
	scene.AddLightSource(lamp2Position);

	scene.SetLightning(LightMode::PHONG_LIGHTNING);
	m_Renderer->BeginScene(scene);
	{
		glm::mat4 triangleMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f));
		glm::mat4 quadMatrix     = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, 0.0f));
		glm::mat4 cubeMatrix     = glm::translate(glm::mat4(1.0f), glm::vec3( 2.0f, 0.0f, 0.0f));

		m_Renderer->DrawTriangle(triangleMatrix, {0.2, 0.3, 0.8, 1.0});
		m_Renderer->DrawQuad(quadMatrix, { 0.2, 0.3, 0.8, 1.0 });
		m_Renderer->DrawCube(cubeMatrix, { 0.2, 0.3, 0.8, 1.0 });
	}
	m_Renderer->EndScene();

	scene.SetLightning(LightMode::FLAT_COLOR);
	m_Renderer->BeginScene(scene);
	{
		glm::mat4 lamp1Matrix = glm::translate(glm::mat4(1.0f), lamp1Position);
		glm::mat4 lamp2Matrix = glm::translate(glm::mat4(1.0f), lamp2Position);
		
		m_Renderer->DrawCube(lamp1Matrix, m_LampTexture);
		m_Renderer->DrawCube(lamp2Matrix, m_LampTexture);
	}
	m_Renderer->EndScene();
}
