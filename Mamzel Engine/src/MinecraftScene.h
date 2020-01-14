#pragma once

#include <memory>
#include <deque>

#include "core/Application.h"

#include <glm/glm.hpp>

class MinecraftScene : public Application
{
private:
	void DrawOpenGL() override;
	void DrawGui() override;

private:
	std::vector<float> m_FrameTimes;

	const char* m_CurrentLightning = "Flat Color";
	const char* m_CurrentDrawMode = "Fill";

	glm::vec3 m_SunDirection = glm::vec3(1.0f, -0.5f, 0.0f);
	float m_SunIntensity = 0.7f;
	glm::vec3 m_SunDiffColor = glm::vec3(1.0f), m_SunSpecColor = glm::vec3(1.0f);

	float m_Lamp1Range = 50.0f, m_Lamp2Range = 50.0f;
	glm::vec3 m_Lamp1Pos = glm::vec3(-2.0f, 0.0f, -2.0f), m_Lamp2Pos = glm::vec3(2.0f, 0.0f, 2.0f);
	glm::vec3 m_Lamp1DiffColor = glm::vec3(1.0f), m_Lamp2DiffColor = glm::vec3(1.0f);
	glm::vec3 m_Lamp1SpecColor = glm::vec3(1.0f), m_Lamp2SpecColor = glm::vec3(1.0f);

	glm::vec3 m_ModelPos = glm::vec3(-5.0f, -0.5f, -5.0f);
	glm::vec4 m_ModelRotate = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	float m_ModelScale = 0.002f;

	std::shared_ptr<Model> m_WolfModel;

public:
	MinecraftScene();
	~MinecraftScene();
};

