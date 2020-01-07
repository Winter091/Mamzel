#include "Light.h"

Light::Light()
	: m_Position(0.0f), m_Attenuation(0.0f), m_DiffuseColor(1.0f), m_SpecularColor(1.0f)
{
	SetRange(50.0f);
}

Light::Light(const glm::vec3& position)
	: m_Position(position), m_Attenuation(0.0f), m_DiffuseColor(1.0f), m_SpecularColor(1.0f)
{
	SetRange(50.0f);
}

Light::Light(const glm::vec3& position, const float range)
	: m_Position(position), m_Attenuation(0.0f), m_DiffuseColor(1.0f), m_SpecularColor(1.0f)
{
	SetRange(range);
}

Light::~Light()
{
}

void Light::SetRange(float newRange)
{
	m_Range = newRange;
	m_Attenuation = glm::vec3(1.0f, 4.5f / newRange, 75.0f / (newRange * newRange));
}

void Light::SetDiffuseColor(const glm::vec3& color)
{
	m_DiffuseColor = color;
}

void Light::SetSpecularColor(const glm::vec3& color)
{
	m_SpecularColor = color;
}
