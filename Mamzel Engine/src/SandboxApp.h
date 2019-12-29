#pragma once

#include <memory>

#include "core/Application.h"

class SandboxApp : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

	std::shared_ptr<Texture> m_LampTexture;

public:
	SandboxApp();
	~SandboxApp();

};

