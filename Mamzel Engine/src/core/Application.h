#pragma once

#include <chrono>
#include <memory>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../renderer/buffers/VertexBuffer.h"
#include "../renderer/buffers/VertexBufferLayout.h"
#include "../renderer/buffers/IndexBuffer.h"
#include "../renderer/buffers/VertexArray.h"
#include "../renderer/Shader.h"
#include "../renderer/Renderer.h"
#include "../renderer/RenderData.h"
#include "../renderer/RenderCommand.h"

#include "../scene/PerspectiveCamera.h"
#include "../scene/TextureLibrary.h"
#include "../scene/Model.h"
#include "../scene/Scene.h"

#include "../util/ErrorHandling.h"
#include "../util/Input.h"

class Application
{
protected:

	GLFWwindow* m_Window;

	std::chrono::time_point<std::chrono::steady_clock> m_StartTime, m_LastTime;
	float m_TimeSinceStart, m_FrameTime;

	std::shared_ptr<PerspectiveCamera> m_Camera;

protected:
	// To be defined by user
	virtual void DrawOpenGL() = 0;
	virtual void DrawGui() = 0;

private:

	// Holding the reference to update camera's aspect ratio on window resize
	static std::shared_ptr<PerspectiveCamera> s_CameraRef;
	static void OnWindowResize(GLFWwindow* window, int width, int height);
	
	GLFWwindow* InitWindow(int w, int h, bool useVSync);

public:

	Application(unsigned int windowWidth, unsigned int windowHeight, bool useVSync);
	~Application();

	void Run();
};
