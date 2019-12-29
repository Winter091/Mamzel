#pragma once

class Texture
{
private:
	unsigned int m_TextureID;

public:
	Texture();
	Texture(const char* path);
	~Texture();

	void SetWrapAndFilterMode(int wrapMode, int filterMode);

	void Bind();
	void Unbind();
};