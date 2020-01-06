#include "MinecraftScene.h"

#include <iostream>

MinecraftScene::MinecraftScene()
	: Application(1600, 900, true)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.1f, 1.0f);

	TextureLibrary::Load("grass", "res/textures/grass.png");
	TextureLibrary::Load("oak_planks", "res/textures/planks_oak.png");
	TextureLibrary::Load("glass", "res/textures/glass.png");
	TextureLibrary::Load("door_lower", "res/textures/door_wood_lower.png");
	TextureLibrary::Load("door_upper", "res/textures/door_wood_upper.png");
	TextureLibrary::Load("redstone_lamp", "res/textures/redstone_lamp.png");
	TextureLibrary::Load("moon", "res/textures/moon_cut.png");
	TextureLibrary::Load("stars", "res/textures/stars.png");

	TextureLibrary::SetWrapAndFilterMode("grass", GL_REPEAT, GL_NEAREST);
	TextureLibrary::SetScale("grass", 100.0f);

	TextureLibrary::SetWrapAndFilterMode("stars", GL_REPEAT, GL_NEAREST);
	TextureLibrary::SetScale("stars", 5.0f);
}

MinecraftScene::~MinecraftScene()
{
	
}

void MinecraftScene::DrawGui()
{	
	ImGui::Begin("Gui");
	ImGui::Text("Frame takes %.3f ms. (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	static const char* items[] = { "Flat Color", "Phong", "Blinn-Phong" };
	if (ImGui::BeginCombo("Lightning", m_CurrentLightning)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < 3; n++)
		{
			bool is_selected = (m_CurrentLightning == items[n]); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(items[n], is_selected))
				m_CurrentLightning = items[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
		}
		ImGui::EndCombo();
	}

	ImGui::SliderFloat("Lamp1", &lamp1Range, 5, 500);
	ImGui::SliderFloat("Lamp2", &lamp2Range, 5, 500);
	ImGui::SliderFloat("Moon", &moonRange, 5, 500);

	ImGui::End();
}

void MinecraftScene::DrawOpenGL()
{
	Renderer::SetClearColor(0.0f, 0.0f, 0.0f);
	Renderer::Clear();

	static glm::vec3 lamp1Position = glm::vec3(3.0, 0.0, 3.0);
	static glm::vec3 lamp2Position = glm::vec3(-2.0, 0.0, -2.0);
	static glm::vec3 moonPosition = glm::vec3(-10.0, 20.0, -100.0);

	Scene scene;
	scene.SetCamera(m_Camera);

	std::shared_ptr<PointLight> lamp1 = std::make_shared<PointLight>(lamp1Position, lamp1Range);
	std::shared_ptr<PointLight> lamp2 = std::make_shared<PointLight>(lamp2Position, lamp2Range);
	std::shared_ptr<PointLight> moon  = std::make_shared<PointLight>(moonPosition, moonRange);

	lamp1->SetDiffuseColor({ 1.0, 0.0, 0.0 });
	lamp1->SetSpecularColor({ 0.0, 0.0, 1.0 });

	scene.AddPointLight(lamp1);
	scene.AddPointLight(lamp2);
	scene.AddPointLight(moon);

	LightMode curr;
	if (m_CurrentLightning == "Flat Color")
		curr = LightMode::FLAT_COLOR;
	else if (m_CurrentLightning == "Phong")
		curr = LightMode::PHONG_LIGHTNING;
	else if (m_CurrentLightning == "Blinn-Phong")
		curr = LightMode::BLINN_PHONG_LIGHTNING;

	scene.SetLightning(curr);
	Renderer::BeginScene(scene);
	{
		// Floor
		Renderer::DrawQuad({ 0.0, -0.5, 0.0 }, { 1.0, 0.0, 0.0, 270.0 }, glm::vec3(100.0f), TextureLibrary::Get("grass"));

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

	scene.SetLightning(LightMode::FLAT_COLOR);
	Renderer::BeginScene(scene);
	{	
		// Lamps
		Renderer::DrawCube(lamp1Position, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("redstone_lamp"));
		Renderer::DrawCube(lamp2Position, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(1.0f), TextureLibrary::Get("redstone_lamp"));

		// Moon
		Renderer::DrawQuad(moonPosition, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(5.0f), TextureLibrary::Get("moon"));

		// Stars
		Renderer::DrawQuad({ 0.0f, 20.0f, -105.0f }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(300.0f), TextureLibrary::Get("stars"));
	}
	Renderer::EndScene();
}
