#include "SandboxApp.h"

SandboxApp::SandboxApp()
	: Application(1600, 900, true)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.1f, 1.0f);

	TextureLibrary::Load("cobblestone", "res/textures/cobblestone.png");
	TextureLibrary::Load("oak_planks", "res/textures/planks_oak.png");
	TextureLibrary::Load("glass", "res/textures/glass.png");
	TextureLibrary::Load("door_lower", "res/textures/door_wood_lower.png");
	TextureLibrary::Load("door_upper", "res/textures/door_wood_upper.png");
	TextureLibrary::Load("redstone_lamp", "res/textures/redstone_lamp.png");
	TextureLibrary::Load("moon", "res/textures/moon.png");

	TextureLibrary::SetWrapAndFilterMode("cobblestone", GL_REPEAT, GL_NEAREST);
	TextureLibrary::SetScale("cobblestone", 100.0f);
}

SandboxApp::~SandboxApp()
{
	
}

void SandboxApp::DrawGui()
{
	ImGui::Begin("Gui");
	ImGui::Text("Frame takes %.3f ms. (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Checkbox("Lightning 1", &usePhong1);
	ImGui::Checkbox("Lightning 2", &usePhong2);
	ImGui::End();
}

void SandboxApp::DrawOpenGL()
{
	Renderer::SetClearColor(0.0f, 0.0f, 0.0f);
	Renderer::Clear();

	static glm::vec3 lamp1Position = glm::vec3(2.0, 0.0, 2.0);
	static glm::vec3 lamp2Position = glm::vec3(-2.0, 0.0, -2.0);

	Scene scene;
	scene.SetCamera(m_Camera);
	scene.AddLightSource(lamp1Position);
	scene.AddLightSource(lamp2Position);

	scene.SetLightning(usePhong1 ? LightMode::PHONG_LIGHTNING : LightMode::FLAT_COLOR);
	Renderer::BeginScene(scene);
	{
		// Floor
		Renderer::DrawQuad({ 0.0, -0.5, 0.0 }, { 1.0, 0.0, 0.0, 90.0 }, glm::vec3(100.0f), TextureLibrary::Get("cobblestone"));

		// Layer 1
		for (int x = -1; x <= 1; x++)
			for (int y = 0; y <= 2; y++)
				if (!(x == 0 && y == 1))
					Renderer::DrawCube({ x, y, -1.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("oak_planks"));

		// Layer 2
		for (int x = -1; x <= 1; x++)
			Renderer::DrawCube({ x, 2.0, 0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("oak_planks"));

		Renderer::DrawCube({ -1.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("oak_planks"));
		Renderer::DrawCube({  1.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("oak_planks"));

		// Layer 3
		for (int x = -1; x <= 1; x++)
			for (int y = 0; y <= 2; y++)
				if (!(x == 0 && y == 1) && !(x == 0 && y == 0))
					Renderer::DrawCube({ x, y, 1.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("oak_planks"));

		// Windows
		Renderer::DrawCube({  0.0, 1.0, -1.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("glass"));
		Renderer::DrawCube({ -1.0, 1.0,  0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("glass"));
		Renderer::DrawCube({  1.0, 1.0,  0.0 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("glass"));

		// Door
		Renderer::DrawQuad({ 0.0, 1.0,  1.5 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("door_upper"));
		Renderer::DrawQuad({ 0.0, 0.0,  1.5 }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("door_lower"));
	}
	Renderer::EndScene();

	scene.SetLightning(usePhong2 ? LightMode::PHONG_LIGHTNING : LightMode::FLAT_COLOR);
	Renderer::BeginScene(scene);
	{	
		// Lamps
		Renderer::DrawCube(lamp1Position, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("redstone_lamp"));
		Renderer::DrawCube(lamp2Position, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("redstone_lamp"));

		// Moon
		Renderer::DrawQuad({-10.0, 20.0, -100.0}, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(20.0f), TextureLibrary::Get("moon"));
	}
	Renderer::EndScene();
}
