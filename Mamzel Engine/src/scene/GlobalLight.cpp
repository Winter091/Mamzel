#include "GlobalLight.h"

GlobalLight::GlobalLight(const glm::vec3& direction, const float intensity)
	: Light(), m_Direction(direction), m_Intensity(intensity)
{
}

GlobalLight::~GlobalLight()
{
}

std::shared_ptr<GlobalLight> GlobalLight::Create(const glm::vec3& direction, const float intensity)
{
	return std::make_shared<GlobalLight>(direction, intensity);
}
