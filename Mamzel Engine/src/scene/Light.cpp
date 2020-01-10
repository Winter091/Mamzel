#include "Light.h"

Light::Light()
	: m_DiffuseColor(1.0f), m_SpecularColor(1.0f)
{
	
}

Light::~Light()
{
}

void Light::SetDiffuseColor(const glm::vec3& color)
{
	m_DiffuseColor = color;
}

void Light::SetSpecularColor(const glm::vec3& color)
{
	m_SpecularColor = color;
}
