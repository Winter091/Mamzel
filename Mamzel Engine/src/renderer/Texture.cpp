#include "Texture.h"
#include "../util/ErrorHandling.h"

#include <GL/glew.h>
#include <stb_image/stb_image.h>

#include <iostream>

Texture::Texture()
	: m_TextureID(0), m_Name(""), m_Path(""), m_Scale(0.0f)
{
}

Texture::Texture(const char* path, const char* name)
{	
	m_Scale = 1.0f;
	m_Name = name;
	m_Path = path;
	
	int w, h, channels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(path, &w, &h, &channels, 0);

	if (!data)
	{
		std::cout << "[Texture] Error! unable to open [" << path << "]\n";
		exit(0);
	}
	
	HANDLE_ERROR(glGenTextures(1, &m_TextureID));
	Bind();

	HANDLE_ERROR(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
	HANDLE_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data));

	HANDLE_ERROR(glGenerateMipmap(GL_TEXTURE_2D));

	// Initial parameters
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	
	stbi_image_free(data);
}

Texture::~Texture()
{
}

std::shared_ptr<Texture> Texture::Create(const char* path, const char* name)
{
	return std::make_shared<Texture>(path, name);
}

void Texture::SetWrapAndFilterMode(int wrapMode, int filterModeMin, int filterModeMag)
{
	Bind();
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode));
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode));
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterModeMin));
	HANDLE_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterModeMag));
}

void Texture::SetScale(float scale)
{
	m_Scale = scale;
}

void Texture::Bind(unsigned int slot)
{
	HANDLE_ERROR(glActiveTexture(GL_TEXTURE0 + slot));
	HANDLE_ERROR(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::Unbind()
{
	HANDLE_ERROR(glBindTexture(GL_TEXTURE_2D, 0));
}
