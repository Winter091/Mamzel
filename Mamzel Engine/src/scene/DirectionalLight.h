#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
private:
	float m_Intensity;
	glm::vec3 m_Direction;

public:
	DirectionalLight() = delete;
	DirectionalLight(const glm::vec3& direction, const float intensity = 1.0f);
	virtual ~DirectionalLight();

	static std::shared_ptr<DirectionalLight> Create(const glm::vec3& direction, const float intensity = 1.0f);

	inline const glm::vec3& GetDirection() const { return m_Direction; }
	inline const float GetIntensity() const { return m_Intensity; }

};