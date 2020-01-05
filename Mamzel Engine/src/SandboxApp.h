#pragma once

#include <memory>

#include "core/Application.h"

class SandboxApp : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<Shader> m_Shader;

	float lampPos[3], objPos[3];

public:
	SandboxApp();
	~SandboxApp();
};


