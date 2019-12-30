#include "Application.h"

#include <iostream>

#include "../core/Scene.h"
#include "../util/ErrorHandling.h"
#include "../util/Input.h"

Application::~Application()
{
	m_Camera = nullptr;
	Renderer::Free();
	TextureLibrary::Free();
	glfwDestroyWindow(m_Window);
}

GLFWwindow* Application::InitWindow(int w, int h, bool useVSync)
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init error\n";
		glfwTerminate();
	}

	GLFWwindow* window = glfwCreateWindow(w, h, "OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Window Init Error\n";
		glfwTerminate();
	}

	glfwSetWindowPos(window, 100, 100);
	glfwMakeContextCurrent(window);

	if (useVSync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init error\n";
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return window;
}

Application::Application(unsigned int windowWidth, unsigned int windowHeight, bool useVSync)
{
	m_Window = InitWindow(windowWidth, windowHeight, useVSync);
	m_StartTime = std::chrono::high_resolution_clock::now();
	m_Camera = std::make_shared<PerspectiveCamera>(windowWidth, windowHeight, 45.0f);

	Input::SetWindow(m_Window);
	Renderer::Init();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 440");

}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();

		auto currTime = std::chrono::high_resolution_clock::now();
		m_Time = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - m_StartTime).count() / 1000.0f;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		DrawGui();

		m_Camera->Update();

		DrawOpenGL();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_Window);
	}
}
