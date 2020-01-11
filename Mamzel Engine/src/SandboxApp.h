#pragma once

#include <memory>

#include "core/Application.h"

class SandboxApp : public Application
{
private:
	void DrawOpenGL();
	void DrawGui();

	std::shared_ptr<Model> m_Model;
	std::shared_ptr<Shader> m_Shader;

	glm::vec3 m_Lamp1Pos = glm::vec3(-7.0f, 13.0f, 11.0f);

public:
	SandboxApp();
	~SandboxApp();
};


