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

	const char* m_CurrentLightning = "Blinn-Phong";

	glm::vec3 m_SunDirection = glm::vec3(1.0f, -0.5f, 0.0f);
	float m_SunIntensity = 0.7f;
	glm::vec3 m_SunDiffColor = glm::vec3(1.0f), m_SunSpecColor = glm::vec3(1.0f);

	float m_Lamp1Range = 50.0f, m_Lamp2Range = 50.0f;
	glm::vec3 m_Lamp1Pos = glm::vec3(-2.0f, 0.0f, -2.0f), m_Lamp2Pos = glm::vec3(2.0f, 0.0f, 2.0f);
	glm::vec3 m_Lamp1DiffColor = glm::vec3(1.0f), m_Lamp2DiffColor = glm::vec3(1.0f);
	glm::vec3 m_Lamp1SpecColor = glm::vec3(1.0f), m_Lamp2SpecColor = glm::vec3(1.0f);

public:
	MinecraftScene();
	~MinecraftScene();
};

