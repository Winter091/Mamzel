#pragma once

#include <memory>
#include <string>

class Texture
{
private:
	unsigned int m_TextureID;
	float m_Scale;
	std::string m_Name;

public:
	Texture();
	Texture(const char* path, const std::string& name = "");
	~Texture();

	static std::shared_ptr<Texture> Create(const char* path, const std::string& name = "");

	void SetWrapAndFilterMode(int wrapMode, int filterModeMin, int filterModeMag);
	void SetScale(float scale);
	inline const std::string& GetName() { return m_Name; }

	inline float GetScale() const { return m_Scale; }

	void Bind(unsigned int slot = 0);
	void Unbind();
};