#pragma once

class Texture
{
private:
	unsigned int m_TextureID;
	float m_Scale;

public:
	Texture();
	Texture(const char* path);
	~Texture();

	void SetWrapAndFilterMode(int wrapMode, int filterMode);
	void SetScale(float scale);

	inline float GetScale() const { return m_Scale; }

	void Bind();
	void Unbind();
};