#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../util/ErrorHandling.h"

class RenderCommand
{
public:
	static void SetClearColor(float r, float g, float b, float a = 1.0f);
	static void SetClearColor(const glm::vec4& color);

	static void Clear();
};