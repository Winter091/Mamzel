#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include "../renderer/VertexBuffer.h"
#include "../renderer/VertexBufferLayout.h"
#include "../renderer/IndexBuffer.h"
#include "../renderer/VertexArray.h"
#include "../renderer/Shader.h"
#include "../renderer/PerspectiveCamera.h"
#include "../renderer/Renderer.h"

class Application
{
protected:

	GLFWwindow* m_Window;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
	float m_Time;

	std::shared_ptr<PerspectiveCamera> m_Camera;
	std::shared_ptr<Renderer> m_Renderer;

	virtual void DrawOpenGL() = 0;
	virtual void DrawGui() = 0;

private:

	GLFWwindow* InitWindow(int w, int h);

public:

	Application(unsigned int windowWidth, unsigned int windowHeight);
	~Application();

	void Run();
};
