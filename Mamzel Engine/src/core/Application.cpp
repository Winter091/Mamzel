#include "Application.h"

#include <iostream>

std::shared_ptr<PerspectiveCamera> Application::s_CameraRef;

Application::~Application()
{
	m_Camera = nullptr;
	s_CameraRef = nullptr;
	RenderData::Free();
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

	GLFWwindow* window = glfwCreateWindow(w, h, "Mamzel Application", NULL, NULL);
	if (!window)
	{
		std::cout << "Window Init Error\n";
		glfwTerminate();
	}

	//glfwSetWindowPos(window, 100, 100);
	glfwMakeContextCurrent(window);

	if (useVSync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, &Application::OnWindowResize);
	glfwSetScrollCallback(window, &Application::OnMouseScroll);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init error\n";
		glfwTerminate();
	}

	return window;
}

void Application::OnWindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	s_CameraRef->SetAspectRatio((float)width / height);
}

void Application::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	s_CameraRef->ChangeMoveSpeed(yoffset);
}

Application::Application(unsigned int windowWidth, unsigned int windowHeight, bool useVSync)
{	
	m_Window = InitWindow(windowWidth, windowHeight, useVSync);
	m_StartTime = std::chrono::high_resolution_clock::now();
	m_LastTime = m_StartTime;

	m_Camera = PerspectiveCamera::Create((float)windowWidth, (float)windowHeight, 45.0f);
	s_CameraRef = m_Camera;

	Input::SetWindow(m_Window);

	RenderData::Load();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		m_FrameTime = std::chrono::duration_cast<std::chrono::microseconds>(currTime - m_LastTime).count() / 1000.0f;
		m_TimeSinceStart = std::chrono::duration_cast<std::chrono::microseconds>(currTime - m_StartTime).count() / 1000.0f;
		m_LastTime = currTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		DrawGui();

		m_Camera->Update(m_FrameTime);

		DrawOpenGL();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_Window);
	}
}
