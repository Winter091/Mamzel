#pragma once

#include "Light.h"

#include <memory>

class PointLight : public Light
{
private:
	float m_MaxRange;

	glm::vec3 m_Position;
	glm::vec3 m_Attenuation;

public:
	PointLight() = delete;
	PointLight(const glm::vec3& position, const float maxRange = 50.0f);
	virtual ~PointLight();

	static std::shared_ptr<PointLight> Create(const glm::vec3& position, const float maxRange = 50.0f);

	void SetRange(float newRange);

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const float GetRange() const { return m_MaxRange; }
	inline const glm::vec3& GetAttenuation() const { return m_Attenuation; }

};