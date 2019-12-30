#pragma once

#include <memory>

#include "core/Application.h"

class SandboxApp : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

	std::shared_ptr<Texture> m_CobblestoneTexture;
	std::shared_ptr<Texture> m_OakPlanksTexture;
	std::shared_ptr<Texture> m_GlassTexture;
	std::shared_ptr<Texture> m_DoorLowerTexture;
	std::shared_ptr<Texture> m_DoorUpperTexture;
	std::shared_ptr<Texture> m_RedstoneLampTexture;
	std::shared_ptr<Texture> m_MoonTexture;

public:
	SandboxApp();
	~SandboxApp();

};

