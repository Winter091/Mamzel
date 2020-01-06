#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "../renderer/PerspectiveCamera.h"
#include "../renderer/Shader.h"
#include "PointLight.h"

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
	std::vector<std::shared_ptr<PointLight>> m_LightSources;
	LightMode m_LightMode;

public:
	Scene();

	void SetCamera(std::shared_ptr<PerspectiveCamera> camera);
	void SetLightning(LightMode lightning);
	void AddPointLight(std::shared_ptr<PointLight> light);

	inline std::shared_ptr<PerspectiveCamera> GetCamera() const { return m_Camera; }
	inline LightMode GetLightMode() const { return m_LightMode; }
	inline const std::vector<std::shared_ptr<PointLight> >& GetLightSources() const { return m_LightSources; }
};