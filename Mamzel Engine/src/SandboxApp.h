#pragma once

#include <memory>

#include "core/Application.h"

class SandboxApp : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

public:
	SandboxApp();
	~SandboxApp();

};

