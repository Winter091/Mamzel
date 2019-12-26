#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>

#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"
#include "renderer/PerspectiveCamera.h"
#include "renderer/Renderer.h"

class Application
{
private:

	GLFWwindow* m_Window;

	std::unique_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<PerspectiveCamera> m_Camera;
	std::unique_ptr<Renderer> m_Renderer;

	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;

private:

	GLFWwindow* InitWindow(int w, int h);

public:

	Application();
	~Application();

	void Run();
};
