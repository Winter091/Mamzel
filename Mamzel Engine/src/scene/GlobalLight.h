#pragma once

#include "Light.h"

class GlobalLight : public Light
{
private:
	float m_Intensity;
	glm::vec3 m_Direction;

public:
	GlobalLight() = delete;
	GlobalLight(const glm::vec3& direction, const float intensity = 1.0f);
	virtual ~GlobalLight();

	static std::shared_ptr<GlobalLight> Create(const glm::vec3& direction, const float intensity = 1.0f);

	inline const glm::vec3& GetDirection() const { return m_Direction; }
	inline const float GetIntensity() const { return m_Intensity; }

};