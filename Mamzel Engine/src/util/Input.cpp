#include "Input.h"

#include <iostream>

const GLFWwindow* Input::s_WindowRef = nullptr;

Input::Input()
{
}

Input::~Input()
{
	s_WindowRef = nullptr;
}

void Input::SetWindow(const GLFWwindow* window)
{
	s_WindowRef = window;
}

bool Input::KeyPressed(int glfwKeyCode)
{
	if (s_WindowRef == nullptr)
	{
		std::cout << "Input::m_WindowRef is nullptr!\n";
		return false;
	}
	
	if (glfwGetKey((GLFWwindow*)s_WindowRef, glfwKeyCode) == GLFW_PRESS)
		return true;
	return false;
}
