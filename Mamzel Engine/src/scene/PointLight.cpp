#include "PointLight.h"

PointLight::PointLight(const glm::vec3& position, const float maxRange)
	: Light(), m_Position(position)
{
	SetRange(maxRange);
}

PointLight::~PointLight()
{
}

std::shared_ptr<PointLight> PointLight::Create(const glm::vec3& position, const float maxRange)
{
	return std::make_shared<PointLight>(position, maxRange);
}

void PointLight::SetRange(float newRange)
{
	m_MaxRange = newRange;
	m_Attenuation = glm::vec3(1.0f, 4.5f / newRange, 75.0f / (newRange * newRange));
}
