#pragma once

#include <memory>
#include <string>

class Texture
{
private:
	unsigned int m_TextureID;
	float m_Scale;
	std::string m_Name, m_Path;

public:
	Texture();
	Texture(const char* path, const char* name);
	~Texture();

	static std::shared_ptr<Texture> Create(const char* path, const char* name);

	void SetWrapAndFilterMode(int wrapMode, int filterModeMin, int filterModeMag);
	void SetScale(float scale);

	inline const std::string& GetPath() const { return m_Path; }
	inline const std::string& GetName() const { return m_Name; }
	inline float GetScale() const { return m_Scale; }

	void Bind(unsigned int slot = 0);
	void Unbind();
};