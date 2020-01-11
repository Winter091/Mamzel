#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderSources
{
	std::string vertexSrc;
	std::string fragmentSrc;
};

class Shader
{
private:
	int m_ShaderProgramID;
	std::unordered_map<std::string, int> m_Uniforms;

	int getUnifromLocation(const char* name);
	void CheckCompileStatus(int id);
	ShaderSources ParseSources(const char* path);
	int CreateShader(int type, const char* sourceCode);

public:
	Shader();
	Shader(const char* path);
	~Shader();

	static std::shared_ptr<Shader> Create(const char* path);

	void Bind() const;
	void Unbind() const;

	void SetUniform(const char* name, int i1);

	void SetUniform(const char* name, float f1);

	void SetUniform(const char* name, float f1, float f2);

	void SetUniform(const char* name, float f1, float f2, float f3);
	void SetUniform(const char* name, const glm::vec3& vec);

	void SetUniform(const char* name, float f1, float f2, float f3, float f4);
	void SetUniform(const char* name, const glm::vec4& vec);

	void SetUniform(const char* name, const glm::mat4& matrix);
};