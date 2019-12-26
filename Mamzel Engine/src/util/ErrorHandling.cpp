#include "ErrorHandling.h"

#include "GL/glew.h"

#include <iostream>

void clearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

void printErrors(const char* funcName, const char* fileName, int line)
{
	while (int error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << fileName << ":" << line << ":" << funcName << std::endl;
	}
}