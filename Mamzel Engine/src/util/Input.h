#pragma once

#include <GLFW/glfw3.h>

#include <memory>

class Input
{
private:
	static const GLFWwindow* s_WindowRef;

public:
	Input();
	~Input();
	
	static void SetWindow(const GLFWwindow* window);
	static bool KeyPressed(int glfwKeyCode);
};