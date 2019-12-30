#pragma once

#include <memory>

#include "core/Application.h"

class SandboxApp : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

	bool usePhong1 = false, usePhong2 = true;

public:
	SandboxApp();
	~SandboxApp();

};

