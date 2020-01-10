#pragma once

#include <memory>

#include <glm/glm.hpp>

class Light
{
protected:
	glm::vec3 m_DiffuseColor;
	glm::vec3 m_SpecularColor;

	// These are protected, user is not allowed to create this virtual object
	Light();
	virtual ~Light();

public:
	void SetDiffuseColor(const glm::vec3& color);
	void SetSpecularColor(const glm::vec3& color);

	inline const glm::vec3& GetDiffuseColor() const { return m_DiffuseColor; }
	inline const glm::vec3& GetSpecularColor() const { return m_SpecularColor; }
};
