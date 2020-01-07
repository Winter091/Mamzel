#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "../renderer/PerspectiveCamera.h"
#include "../renderer/Shader.h"
#include "Light.h"

enum class LightMode
{
	FLAT_COLOR = 0,
	PHONG_LIGHTNING,
	BLINN_PHONG_LIGHTNING
};

class Scene
{
private:
	std::shared_ptr<PerspectiveCamera> m_Camera;
	std::vector<std::shared_ptr<Light>> m_PointLights;
	LightMode m_LightMode;

	std::shared_ptr<Light> m_GlobalLight;

public:
	Scene();

	void SetCamera(std::shared_ptr<PerspectiveCamera> camera);
	void SetLightning(LightMode lightning);
	void SetGlobalLight(const glm::vec3& direction, float intensity, const glm::vec3& diffuseColor = glm::vec3(1.0f), const glm::vec3& specColor = glm::vec3(1.0f));
	void AddPointLight(std::shared_ptr<Light> light);

	inline std::shared_ptr<PerspectiveCamera> GetCamera() const { return m_Camera; }
	inline LightMode GetLightMode() const { return m_LightMode; }
	inline const std::vector<std::shared_ptr<Light> >& GetPointLights() const { return m_PointLights; }
	inline const std::shared_ptr<Light> GetGlobalLight() const { return m_GlobalLight; }
};