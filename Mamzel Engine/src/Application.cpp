#include "Application.h"

#include <iostream>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "core/Scene.h"
#include "util/ErrorHandling.h"
#include "util/Input.h"

using namespace std;

Application::~Application()
{
	m_VertexBuffer = nullptr;
	m_IndexBuffer = nullptr;
	m_VertexArray = nullptr;
	m_Shader = nullptr;
	m_Renderer = nullptr;
	m_Camera = nullptr;
	glfwDestroyWindow(m_Window);
}

GLFWwindow* Application::InitWindow(int w, int h)
{
	if (!glfwInit())
	{
		cout << "GLFW Init error\n";
		glfwTerminate();
	}

	GLFWwindow* window = glfwCreateWindow(w, h, "OpenGL", NULL, NULL);
	if (!window)
	{
		cout << "Window Init Error\n";
		glfwTerminate();
	}

	glfwSetWindowPos(window, 100, 100);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW Init error\n";
		glfwTerminate();
	}


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return window;
}

Application::Application()
{	
	int windowWidth = 1600;
	int windowHeight = 900;

	m_Window = InitWindow(windowWidth, windowHeight);
	Input::SetWindow(m_Window);

	m_StartTime = std::chrono::high_resolution_clock::now();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 440");

	float vertices[] = {
		-0.5f, -0.5f,  0.0f,     0.0f, 0.0f,
		-0.5f,  0.5f,  0.0f,     0.0f, 1.0f,
		 0.5f,  0.5f,  0.0f,     1.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,     1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2, 
		2, 3, 0
	};

	m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	m_IndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices));
	VertexBufferLayout layout = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_Coord" }
	};

	m_VertexArray = std::make_shared<VertexArray>(m_VertexBuffer, m_IndexBuffer, layout);

	//m_Shader = std::make_shared<Shader>("res/shaders/vertexColored.vert", "res/shaders/mandelbrotSet.frag");

	m_Camera = std::make_shared<PerspectiveCamera>(windowWidth, windowHeight, 45.0f);
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.05f, 0.8f);

	m_Renderer = std::make_shared<Renderer>();
	m_Renderer->SetClearColor(0.15f, 0.15f, 0.18f);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
		
		auto currTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - m_StartTime).count() / 1000.0f;

		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Gui");                          
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		m_Camera->Update();

		static glm::vec3 lampPosition(-2.0f, 2.0f, 3.0f);

		m_Renderer->Clear();

		Scene scene;

		scene.SetCamera(m_Camera);
		scene.SetLightning(LightMode::PHONG_LIGHTNING);
		scene.AddLightSource(lampPosition);
		m_Renderer->BeginScene(scene);
		{
			glm::mat4 cubeMatrix = glm::rotate(glm::mat4(1.0), time, glm::vec3(1.0));
			m_Renderer->DrawCube(cubeMatrix, { 0.2, 0.3, 0.8, 1.0 });
		}
		m_Renderer->EndScene();

		scene.SetLightning(LightMode::FLAT_COLOR);
		m_Renderer->BeginScene(scene);
		{
			m_Renderer->DrawCube(lampPosition, { 1.0, 1.0, 1.0, 0.0 }, { 0.8, 0.8, 0.8 });
		}
		m_Renderer->EndScene();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_Window);
	}
}
