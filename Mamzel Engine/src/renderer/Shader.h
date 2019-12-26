#pragma once

#include <string>
#include <unordered_map>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

class Shader
{
private:
	int m_ShaderProgramID;
	std::unordered_map<std::string, int> m_Uniforms;

	int getUnifromLocation(const char* name);
	void CheckCompileStatus(int id);
	std::string ParseSource(const char* path);
	int CreateShader(int type, const char* path);

public:
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void setUniform(const char* name, float f1);
	void setUniform(const char* name, float f1, float f2);
	void setUniform(const char* name, float f1, float f2, float f3);
	void setUniform(const char* name, float f1, float f2, float f3, float f4);

	void setUniform(const char* name, const glm::mat4& matrix);
};