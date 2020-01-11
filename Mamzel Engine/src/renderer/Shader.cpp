#include "Shader.h"
#include "../util/ErrorHandling.h"

#include <GL/glew.h>

#include <fstream>
#include <iostream>

enum class ShaderType
{
	NONE = 0,
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

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

ShaderSources Shader::ParseSources(const char* path)
{
	std::ifstream file(path);
	std::string line, vertexCode, fragmentCode;

	if (!file)
	{
		std::cout << "[Shader] Error! unable to open [" << path << "]\n";
		exit(0);
	}

	ShaderType currShader = ShaderType::NONE;

	while (getline(file, line))
	{
		if (line.find("#VERTEX SHADER") != std::string::npos)
			currShader = ShaderType::VERTEX_SHADER;
		else if (line.find("#FRAGMENT SHADER") != std::string::npos)
			currShader = ShaderType::FRAGMENT_SHADER;
		else
		{
			switch (currShader)
			{
				case ShaderType::VERTEX_SHADER: vertexCode += line + '\n'; break;
				case ShaderType::FRAGMENT_SHADER: fragmentCode += line + '\n'; break;
			}
		}
	}

	return { vertexCode, fragmentCode };
}

int Shader::CreateShader(int type, const char* sourceCode)
{
	int id = glCreateShader(type);
	glShaderSource(id, 1, &sourceCode, nullptr);
	glCompileShader(id);
	this->CheckCompileStatus(id);
	return id;
}

Shader::Shader()
	: m_ShaderProgramID(-1)
{
}

Shader::Shader(const char* path)
{
	ShaderSources src = this->ParseSources(path);
	
	int vertexShaderID = this->CreateShader(GL_VERTEX_SHADER, src.vertexSrc.c_str());
	int fragmentShaderID = this->CreateShader(GL_FRAGMENT_SHADER, src.fragmentSrc.c_str());

	this->m_ShaderProgramID = glCreateProgram();
	HANDLE_ERROR(glAttachShader(m_ShaderProgramID, vertexShaderID));
	HANDLE_ERROR(glAttachShader(m_ShaderProgramID, fragmentShaderID));
	HANDLE_ERROR(glLinkProgram(m_ShaderProgramID));
	HANDLE_ERROR(glValidateProgram(m_ShaderProgramID));

	HANDLE_ERROR(glDetachShader(m_ShaderProgramID, vertexShaderID));
	HANDLE_ERROR(glDetachShader(m_ShaderProgramID, fragmentShaderID));

	HANDLE_ERROR(glDeleteShader(vertexShaderID));
	HANDLE_ERROR(glDeleteShader(fragmentShaderID));
}

Shader::~Shader()
{
	HANDLE_ERROR(glDeleteProgram(this->m_ShaderProgramID));
}

std::shared_ptr<Shader> Shader::Create(const char* path)
{
	return std::make_shared<Shader>(path);
}

void Shader::Bind() const
{
	HANDLE_ERROR(glUseProgram(this->m_ShaderProgramID));
}

void Shader::Unbind() const
{
	HANDLE_ERROR(glUseProgram(0));
}

void Shader::SetUniform(const char* name, int i1)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform1i(location, i1));
}

void Shader::SetUniform(const char* name, float f1) 
{
	int location = this->getUnifromLocation(name);
	
	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform1f(location, f1));
}

void Shader::SetUniform(const char* name, float f1, float f2)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform2f(location, f1, f2));
}

void Shader::SetUniform(const char* name, float f1, float f2, float f3)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform3f(location, f1, f2, f3));
}

void Shader::SetUniform(const char* name, const glm::vec3& vec)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform3f(location, vec.x, vec.y, vec.z));
}

void Shader::SetUniform(const char* name, float f1, float f2, float f3, float f4)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform4f(location, f1, f2, f3, f4));
}

void Shader::SetUniform(const char* name, const glm::vec4& vec)
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
}

void Shader::SetUniform(const char* name, const glm::mat4& matrix) 
{
	int location = this->getUnifromLocation(name);

	if (location == -1)
		std::cout << "[Shader] Warning! [" << name << "] uniform location is -1!\n";
	else
		HANDLE_ERROR(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}
