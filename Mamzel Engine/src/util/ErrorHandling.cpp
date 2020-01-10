#include "ErrorHandling.h"

#include <GL/glew.h>

#include <iostream>
#include <filesystem>

void clearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

void printErrors(const char* funcName, const char* fileName, int line)
{
	while (int error = glGetError())
	{
		const GLubyte* err = gluErrorString(error);
		std::cout << "[OpenGL Error] (" << err << "): " << std::filesystem::path(fileName).filename() << ":" << line << ":" << funcName << std::endl;
	}
}