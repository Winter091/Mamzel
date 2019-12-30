#include "TextureLibrary.h"

#include <iostream>

// Static member init
std::unordered_map<std::string, std::shared_ptr<Texture>> TextureLibrary::s_Textures;

void TextureLibrary::Free()
{
	s_Textures.clear();
}

void TextureLibrary::Load(const char* name, const char* path)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);
	s_Textures[name] = texture;
}

std::shared_ptr<Texture> TextureLibrary::Get(const char* name)
{
	if (s_Textures.find(name) != s_Textures.end())
		return s_Textures[name];

	std::cout << "TextureLibrary: [" << name << "] texture is not loaded!\n";
	exit(0);
}

void TextureLibrary::SetWrapAndFilterMode(const char* name, int wrapMode, int filterMode)
{
	if (s_Textures.find(name) == s_Textures.end())
	{
		std::cout << "TextureLibrary: [" << name << "] texture is not loaded!\n";
		exit(0);
	}

	s_Textures[name]->SetWrapAndFilterMode(wrapMode, filterMode);
}

void TextureLibrary::SetScale(const char* name, float newScale)
{
	if (s_Textures.find(name) == s_Textures.end())
	{
		std::cout << "TextureLibrary: [" << name << "] texture is not loaded!\n";
		exit(0);
	}

	s_Textures[name]->SetScale(newScale);
}
