#include "SandboxApp.h"

#include <iostream>

SandboxApp::SandboxApp()
	: Application(1600, 900, true)
{
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.1f, 1.0f);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f,	   0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,	   0.0f, 0.0f, 1.0f
	};
	VertexBufferLayout layout = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 3, "a_Normal" }
	};

	m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	m_VertexArray = std::make_shared<VertexArray>(m_VertexBuffer, layout);
	m_Shader = std::make_shared<Shader>("res/shaders/fun/train.vert", "res/shaders/fun/train.frag");
}

SandboxApp::~SandboxApp()
{

}

void SandboxApp::DrawGui()
{
	ImGui::Begin("Gui");
	ImGui::Text("Frame takes %.3f ms. (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat3("Object", objPos, -2.0, 2.0);
	ImGui::SliderFloat3("Lamp", lampPos, -2.0, 2.0);
	ImGui::End();
}

void SandboxApp::DrawOpenGL()
{
	Renderer::SetClearColor(0.15f, 0.15f, 0.15f);
	Renderer::Clear();

	glm::vec3 lampPosition = glm::vec3(lampPos[0], lampPos[1], lampPos[2]);
	glm::vec3 objectPosition = glm::vec3(objPos[0], objPos[1], objPos[2]);

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), objectPosition);
	m_Shader->Bind();
	m_Shader->SetUniform("u_ObjectTransform", modelMatrix);
	m_Shader->SetUniform("u_LightPos", lampPosition);
	m_Shader->SetUniform("u_CameraPos", m_Camera->GetPosition());

	Scene scene;
	scene.SetCamera(m_Camera);
	//scene.AddPointLight(lampPosition);

	Renderer::BeginScene(scene);
	{
		Renderer::DrawCube(glm::translate(glm::mat4(1.0f), lampPosition) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
		Renderer::DrawCustomShape(m_VertexArray, m_Shader, modelMatrix);
	}
	Renderer::EndScene();
}
