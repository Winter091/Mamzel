#include "SandboxApp.h"

SandboxApp::SandboxApp()
	: Application(1600, 900, true)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.05f, 0.8f);

	m_Renderer->SetClearColor(0.0f, 0.0f, 0.0f);

	m_CobblestoneTexture = std::make_shared<Texture>("res/textures/cobblestone.png");
	m_CobblestoneTexture->SetWrapAndFilterMode(GL_REPEAT, GL_NEAREST);
	m_CobblestoneTexture->SetScale(100.0f);

	m_OakPlanksTexture = std::make_shared<Texture>("res/textures/planks_oak.png");
	m_GlassTexture = std::make_shared<Texture>("res/textures/glass.png");

	m_DoorLowerTexture = std::make_shared<Texture>("res/textures/door_wood_lower.png");
	m_DoorUpperTexture = std::make_shared<Texture>("res/textures/door_wood_upper.png");

	m_RedstoneLampTexture = std::make_shared<Texture>("res/textures/redstone_lamp.png");

	m_MoonTexture = std::make_shared<Texture>("res/textures/moon.png");
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
		// Floor
		m_Renderer->DrawQuad({ 0.0, -0.5, 0.0 }, { 1.0, 0.0, 0.0, 90.0 }, glm::vec3(100.0f), m_CobblestoneTexture);

		// Layer 1
		for (int x = -1; x <= 1; x++)
			for (int y = 0; y <= 2; y++)
				if (!(x == 0 && y == 1))
					m_Renderer->DrawCube({ x, y, -1.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_OakPlanksTexture);

		// Layer 2
		for (int x = -1; x <= 1; x++)
			m_Renderer->DrawCube({ x, 2.0, 0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_OakPlanksTexture);

		m_Renderer->DrawCube({ -1.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_OakPlanksTexture);
		m_Renderer->DrawCube({  1.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_OakPlanksTexture);

		// Layer 3
		for (int x = -1; x <= 1; x++)
			for (int y = 0; y <= 2; y++)
				if (!(x == 0 && y == 1) && !(x == 0 && y == 0))
					m_Renderer->DrawCube({ x, y, 1.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_OakPlanksTexture);

		// Windows
		m_Renderer->DrawCube({  0.0, 1.0, -1.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_GlassTexture);
		m_Renderer->DrawCube({ -1.0, 1.0,  0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_GlassTexture);
		m_Renderer->DrawCube({  1.0, 1.0,  0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_GlassTexture);

		// Door
		m_Renderer->DrawQuad({ 0.0, 1.0,  1.5 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_DoorUpperTexture);
		m_Renderer->DrawQuad({ 0.0, 0.0,  1.5 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_DoorLowerTexture);
	}
	m_Renderer->EndScene();

	scene.SetLightning(LightMode::FLAT_COLOR);
	m_Renderer->BeginScene(scene);
	{	
		// Lamps
		m_Renderer->DrawCube(lamp1Position, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_RedstoneLampTexture);
		m_Renderer->DrawCube(lamp2Position, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), m_RedstoneLampTexture);

		// Moon
		m_Renderer->DrawQuad({-10.0, 20.0, -100.0}, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(20.0f), m_MoonTexture);
	}
	m_Renderer->EndScene();
}
