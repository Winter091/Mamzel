#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "../renderer/Texture.h"

class TextureLibrary
{
private:
	static std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;

public:

	TextureLibrary() = delete;

	static void Free();

	static void Load(const char* textureName, const char* path);
	static std::shared_ptr<Texture> Get(const char* textureName);

	static void SetWrapAndFilterMode(const char* textureName, int wrapMode, int filterMode);
	static void SetScale(const char* textureName, float newScale);
};
