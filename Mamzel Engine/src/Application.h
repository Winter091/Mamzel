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

	std::shared_ptr<PerspectiveCamera> m_Camera;
	std::shared_ptr<Renderer> m_Renderer;

	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;

private:

	GLFWwindow* InitWindow(int w, int h);

public:

	Application();
	~Application();

	void Run();
};
