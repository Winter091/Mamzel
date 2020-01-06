#pragma once

#include <memory>
#include <deque>

#include "core/Application.h"

class MinecraftScene : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

	const char* m_CurrentLightning = "Flat Color";
	float lamp1Range, lamp2Range, moonRange;

public:
	MinecraftScene();
	~MinecraftScene();
};

