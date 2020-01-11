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

bool Input::MouseLeftButtonPressed()
{
	return glfwGetMouseButton((GLFWwindow*)s_WindowRef, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool Input::MouseRightButtonPressed()
{
	return glfwGetMouseButton((GLFWwindow*)s_WindowRef, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

std::pair<double, double> Input::GetMousePos()
{
	std::pair<double, double> mousePos;
	glfwGetCursorPos((GLFWwindow*)s_WindowRef, &mousePos.first, &mousePos.second);
	return mousePos;
}

void Input::SetMouseInputMode(int mode)
{
	glfwSetInputMode((GLFWwindow*)s_WindowRef, GLFW_CURSOR, mode);
}
