#include "RenderCommand.h"

void RenderCommand::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void RenderCommand::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void RenderCommand::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
