#include "Application.h"

#include <iostream>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

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
	//glfwSwapInterval(1);

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

	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));
	VertexBufferLayout layout = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_Coord" }
	};

	m_VertexArray = std::make_unique<VertexArray>(m_VertexBuffer, m_IndexBuffer, layout);

	m_Shader = std::make_unique<Shader>("res/shaders/vertexColored.vert", "res/shaders/mandelbrotSet.frag");

	m_Camera = std::make_unique<PerspectiveCamera>(windowWidth, windowHeight, 45.0f);
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_Camera->SetMoveSpeedAndMouseSens(0.05f, 0.8f);

	m_Renderer = std::make_unique<Renderer>();
	m_Renderer->SetClearColor(0.15f, 0.15f, 0.18f);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
		
		auto currTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - m_StartTime).count() / 1000.0f;

		static float translation[2] = { 0.0f, 0.0f };
		static float coeffs[2] = { 0.0f, 0.0f };
		static float divideCoeff = 35.0f;
		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Gui");                          

			ImGui::ColorEdit4("Color", color);
			ImGui::SliderFloat2("Translation", translation, -2.0f, 2.0f);
			ImGui::SliderFloat2("Coeffs", coeffs, -1.0f, 1.0f);
			ImGui::SliderFloat("Brightness", &divideCoeff, 1.0f, 200.0f);

			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}

		m_Shader->Bind();
		m_Shader->setUniform("u_divideCoeff", divideCoeff);
		m_Shader->setUniform("u_realCoeff", coeffs[0]);
		m_Shader->setUniform("u_imagCoeff", coeffs[1]);
		m_Shader->setUniform("u_translation", translation[0], translation[1]);
		m_Shader->setUniform("u_color", color[0], color[1], color[2], color[3]);

		m_Camera->Update();

		glm::mat4 quadMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(abs(sin(time))));
		glm::mat4 triangleMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f)) * glm::rotate(glm::mat4(1.0f), time, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 fractalMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));

		m_Renderer->Clear();

		m_Renderer->BeginScene(m_Camera->GetMatrixVP());
		m_Renderer->DrawUserShape(m_VertexArray, m_Shader, fractalMatrix);
		m_Renderer->DrawQuad(quadMatrix, {0.8, 0.1, 0.1, 0.5});
		m_Renderer->DrawTriangle(triangleMatrix, {0.2, 0.3, 0.8, 0.5});
		m_Renderer->EndScene();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_Window);
	}
}
