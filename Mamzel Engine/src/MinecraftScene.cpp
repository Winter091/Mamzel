#include "MinecraftScene.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

MinecraftScene::MinecraftScene()
	: Application(1600, 900, false)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.004f, 0.08f);

	TextureLibrary::Load("grass", "res/textures/grass.png");
	TextureLibrary::SetWrapAndFilterMode("grass", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
	TextureLibrary::SetScale("grass", 100.0f);

	TextureLibrary::Load("oak_planks", "res/textures/planks_oak.png");
	TextureLibrary::SetWrapAndFilterMode("oak_planks", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

	TextureLibrary::Load("glass", "res/textures/glass.png");
	TextureLibrary::SetWrapAndFilterMode("glass", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

	TextureLibrary::Load("door_lower", "res/textures/door_wood_lower.png");
	TextureLibrary::SetWrapAndFilterMode("door_lower", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

	TextureLibrary::Load("door_upper", "res/textures/door_wood_upper.png");
	TextureLibrary::SetWrapAndFilterMode("door_upper", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

	TextureLibrary::Load("redstone_lamp", "res/textures/redstone_lamp.png");
	TextureLibrary::SetWrapAndFilterMode("redstone_lamp", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

	TextureLibrary::Load("moon", "res/textures/moon_cut.png");
	TextureLibrary::SetWrapAndFilterMode("moon", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

	TextureLibrary::Load("stars", "res/textures/stars.png");
	TextureLibrary::SetWrapAndFilterMode("stars", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
	TextureLibrary::SetScale("stars", 5.0f);

	m_WolfModel = Model::Create("res/models/lowpolywolf/wolf.obj");
	//m_WolfModel = Model::Create("res/models/nanosuit/nanosuit.obj");
}

MinecraftScene::~MinecraftScene()
{
	
}

void MinecraftScene::DrawGui()
{	
	ImGui::Begin("Gui");
	ImGui::Text("Frame takes %.3f ms. (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (m_FrameTimes.size() < ImGui::GetIO().Framerate)
		m_FrameTimes.push_back(1000.0f / ImGui::GetIO().Framerate);
	else
	{
		std::rotate(m_FrameTimes.begin(), m_FrameTimes.begin() + 1, m_FrameTimes.end());
		m_FrameTimes[m_FrameTimes.size() - 1] = 1000.0f / ImGui::GetIO().Framerate;
	}
	ImGui::PlotLines("Frame Times", m_FrameTimes.data(), (int)m_FrameTimes.size());
		
	static const char* items[] = { "Flat Color", "Phong", "Blinn-Phong" };
	if (ImGui::BeginCombo("Lightning", m_CurrentLightning))
	{
		for (int n = 0; n < 3; n++)
		{
			bool is_selected = (m_CurrentLightning == items[n]); 
			if (ImGui::Selectable(items[n], is_selected))
				m_CurrentLightning = items[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();   
		}
		ImGui::EndCombo();
	}

	static const char* items2[] = { "Points", "Lines", "Fill" };
	if (ImGui::BeginCombo("Draw Mode", m_CurrentDrawMode))
	{
		for (int n = 0; n < 3; n++)
		{
			bool is_selected = (m_CurrentDrawMode == items2[n]);
			if (ImGui::Selectable(items2[n], is_selected))
				m_CurrentDrawMode = items2[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (ImGui::CollapsingHeader("Lamp1"))
	{
		ImGui::SliderFloat3("Position##1", &m_Lamp1Pos.x, -15.0f, 15.0f);
		ImGui::ColorEdit3("Diffuse Color##1", &m_Lamp1DiffColor.x);
		ImGui::ColorEdit3("Specular Color##1", &m_Lamp1SpecColor.x);
		ImGui::SliderFloat("Range##1", &m_Lamp1Range, 5, 1000);
	}

	if (ImGui::CollapsingHeader("Lamp2"))
	{
		ImGui::SliderFloat3("Position##2", &m_Lamp2Pos.x, -15.0f, 15.0f);
		ImGui::ColorEdit3("Diffuse Color##2", &m_Lamp2DiffColor.x);
		ImGui::ColorEdit3("Specular Color##2", &m_Lamp2SpecColor.x);
		ImGui::SliderFloat("Range##2", &m_Lamp2Range, 5, 1000);
	}

	if (ImGui::CollapsingHeader("Sun"))
	{
		ImGui::SliderFloat3("Direction##3", &m_SunDirection.x, -1.0f, 1.0f);
		ImGui::ColorEdit3("Diffuse Color##3", &m_SunDiffColor.x);
		ImGui::ColorEdit3("Specular Color##3", &m_SunSpecColor.x);
		ImGui::SliderFloat("Intensity##3", &m_SunIntensity, 0.0f, 1.5f);
	}

	if (ImGui::CollapsingHeader("Model"))
	{
		ImGui::SliderFloat3("Position##4", &m_ModelPos.x, -15.0f, 15.0f);
		ImGui::SliderFloat4("Rotation##4", &m_ModelRotate.x, 0.0f, 360.0f);
		ImGui::SliderFloat("Scale##4", &m_ModelScale, 0.001f, 1.0f);
	}

	ImGui::End();
}

void MinecraftScene::DrawOpenGL()
{
	RenderCommand::SetClearColor(0.0f, 0.0f, 0.0f);
	RenderCommand::Clear();

	if (m_CurrentDrawMode == "Points")
		RenderCommand::SetPolygonMode(GL_POINT);
	else if (m_CurrentDrawMode == "Lines")
		RenderCommand::SetPolygonMode(GL_LINE);
	else if (m_CurrentDrawMode == "Fill")
		RenderCommand::SetPolygonMode(GL_FILL);

	glm::vec3 moonPosition(-10.0, 20.0, -100.0);

	Scene scene;
	scene.SetCamera(m_Camera);

	DirectionalLight sun(m_SunDirection, m_SunIntensity);
	sun.SetDiffuseColor(m_SunDiffColor);
	sun.SetSpecularColor(m_SunSpecColor);

	PointLight lamp1(m_Lamp1Pos, m_Lamp1Range);
	lamp1.SetDiffuseColor(m_Lamp1DiffColor);
	lamp1.SetSpecularColor(m_Lamp1SpecColor);

	PointLight lamp2(m_Lamp2Pos, m_Lamp2Range);
	lamp2.SetDiffuseColor(m_Lamp2DiffColor);
	lamp2.SetSpecularColor(m_Lamp2SpecColor);

	scene.SetDirectionalLight(sun);
	scene.AddPointLight(lamp1);
	scene.AddPointLight(lamp2);

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
		Renderer::DrawCoordinateLines();
		
		// Model
		Renderer::DrawModel(m_WolfModel, m_ModelPos, m_ModelRotate, glm::vec3(m_ModelScale));

		// Floor
		Renderer::DrawQuad(TextureLibrary::Get("grass"), { 0.0, -0.5, 0.0 }, { 1.0, 0.0, 0.0, 270.0 }, glm::vec3(100.0f));

		// House Layer 1
		for (int x = -1; x <= 1; x++)
			for (int y = 0; y <= 2; y++)
				if (!(x == 0 && y == 1))
					Renderer::DrawCube(TextureLibrary::Get("oak_planks"), { x, y, -1.0 });

		// House Layer 2
		for (int x = -1; x <= 1; x++)
			Renderer::DrawCube(TextureLibrary::Get("oak_planks"), { x, 2.0, 0.0 });

		Renderer::DrawCube(TextureLibrary::Get("oak_planks"), { -1.0, 0.0, 0.0 });
		Renderer::DrawCube(TextureLibrary::Get("oak_planks"), {  1.0, 0.0, 0.0 });

		// House Layer 3
		for (int x = -1; x <= 1; x++)
			for (int y = 0; y <= 2; y++)
				if (!(x == 0 && y == 1) && !(x == 0 && y == 0))
					Renderer::DrawCube(TextureLibrary::Get("oak_planks"), { x, y, 1.0 });

		// Windows
		Renderer::DrawCube(TextureLibrary::Get("glass"), { 0.0, 1.0, -1.0 });
		Renderer::DrawCube(TextureLibrary::Get("glass"), { -1.0, 1.0, 0.0 });
		Renderer::DrawCube(TextureLibrary::Get("glass"), {  1.0, 1.0,  0.0 });

		// Door
		Renderer::DrawQuad(TextureLibrary::Get("door_upper"), { 0.0, 1.0,  1.5 });
		Renderer::DrawQuad(TextureLibrary::Get("door_lower"), { 0.0, 0.0,  1.5 });
	}
	Renderer::EndScene();

	scene.SetLightning(LightMode::FLAT_COLOR);
	Renderer::BeginScene(scene);
	{	
		// Lamps
		Renderer::DrawCube(TextureLibrary::Get("redstone_lamp"), m_Lamp1Pos);
		Renderer::DrawCube(TextureLibrary::Get("redstone_lamp"), m_Lamp2Pos);

		// Moon
		Renderer::DrawQuad(TextureLibrary::Get("moon"), moonPosition, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(5.0f));

		// Stars
		Renderer::DrawQuad(TextureLibrary::Get("stars"), { 0.0f, 20.0f, -105.0f }, { 1.0, 1.0, 1.0, 0.0 }, glm::vec3(300.0f));
	}
	Renderer::EndScene();
}
