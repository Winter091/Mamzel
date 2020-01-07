#pragma once

#include <memory>

class Texture
{
private:
	unsigned int m_TextureID;
	float m_Scale;

public:
	Texture();
	Texture(const char* path);
	~Texture();

	static std::shared_ptr<Texture> CreateTexture(const char* path);

	void SetWrapAndFilterMode(int wrapMode, int filterModeMin, int filterModeMag);
	void SetScale(float scale);

	inline float GetScale() const { return m_Scale; }

	void Bind();
	void Unbind();
};