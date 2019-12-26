#include "Shader.h"
#include "../util/ErrorHandling.h"

#include "GL/glew.h"

#include <fstream>
#include <iostream>

int Shader::getUnifromLocation(const char* name)
{
	if (this->m_Uniforms.find(name) == this->m_Uniforms.end())
	{
		this->m_Uniforms[name] = glGetUniformLocation(this->m_ShaderProgramID, name);
	}

	return this->m_Uniforms[name];
}

void Shader::CheckCompileStatus(int id)
{
	int result;
	HANDLE_ERROR(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		HANDLE_ERROR(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = new char[length];
		HANDLE_ERROR(glGetShaderInfoLog(id, length, &length, message));
		std::cout << message << std::endl;
		delete[] message;
		exit(0);
	}
}

std::string Shader::ParseSource(const char* path)
{
	std::ifstream file(path);
	std::string line, code;

	if (!file)
	{
		std::cout << "Error! unable to open [" << path << "]\n";
		exit(0);
	}

	while (getline(file, line))
		code += line + '\n';

	return code;
}

int Shader::CreateShader(int type, const char* path)
{
	int id = glCreateShader(type);
	std::string sourceCode = this->ParseSource(path);
	const char* source = sourceCode.c_str();
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);
	this->CheckCompileStatus(id);
	return id;
}

Shader::Shader()
	: m_ShaderProgramID(-1)
{
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	int vertexShaderID = this->CreateShader(GL_VERTEX_SHADER, vertexPath);
	int fragmentShaderID = this->CreateShader(GL_FRAGMENT_SHADER, fragmentPath);

	this->m_ShaderProgramID = glCreateProgram();
	glAttachShader(m_ShaderProgramID, vertexShaderID);
	glAttachShader(m_ShaderProgramID, fragmentShaderID);
	glLinkProgram(m_ShaderProgramID);
	glValidateProgram(m_ShaderProgramID);

	glDetachShader(m_ShaderProgramID, vertexShaderID);
	glDetachShader(m_ShaderProgramID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

Shader::~Shader()
{
	HANDLE_ERROR(glDeleteProgram(this->m_ShaderProgramID));
}

void Shader::Bind() const
{
	HANDLE_ERROR(glUseProgram(this->m_ShaderProgramID));
}

void Shader::Unbind() const
{
	HANDLE_ERROR(glUseProgram(0));
}

void Shader::setUniform(const char* name, float f1) 
{
	int location = this->getUnifromLocation(name);
	
	if (location == -1)
		std::cout << "Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform1f(location, f1));
}

void Shader::setUniform(const char* name, float f1, float f2)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform2f(location, f1, f2));
}

void Shader::setUniform(const char* name, float f1, float f2, float f3)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform3f(location, f1, f2, f3));
}

void Shader::setUniform(const char* name, float f1, float f2, float f3, float f4)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform4f(location, f1, f2, f3, f4));
}

void Shader::setUniform(const char* name, const glm::mat4& matrix) 
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}
