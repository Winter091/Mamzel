#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const float intensity)
	: Light(), m_Direction(direction), m_Intensity(intensity)
{
}

DirectionalLight::~DirectionalLight()
{
}

std::shared_ptr<DirectionalLight> DirectionalLight::Create(const glm::vec3& direction, const float intensity)
{
	return std::make_shared<DirectionalLight>(direction, intensity);
}
