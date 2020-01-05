#pragma once

#include "glm/glm.hpp"

// Point light
class Light
{
private:
	float m_Range;

	glm::vec3 m_Position;
	glm::vec3 m_Attenuation;

	glm::vec3 m_DiffuseColor;
	glm::vec3 m_SpecularColor;

public:
	Light();
	Light(const glm::vec3& position);
	Light(const glm::vec3& position, const float range);
	~Light();

	void SetRange(float newRange);
	void SetDiffuseColor(const glm::vec3& color);
	void SetSpecularColor(const glm::vec3& color);

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::vec3& GetAttenuation() const { return m_Attenuation; }
	inline const glm::vec3& GetDiffuseColor() const { return m_DiffuseColor; }
	inline const glm::vec3& GetSpecularColor() const { return m_SpecularColor; }
};