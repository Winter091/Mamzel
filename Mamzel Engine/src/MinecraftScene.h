#pragma once

#include <memory>
#include <deque>

#include "core/Application.h"

class MinecraftScene : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

	const char* m_CurrentLightning = "Phong";
	float lamp1Range, lamp2Range, moonRange;
	std::vector<float> m_FrameTimes;

public:
	MinecraftScene();
	~MinecraftScene();
};

