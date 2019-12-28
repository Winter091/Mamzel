#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "../renderer/PerspectiveCamera.h"
#include "../renderer/Shader.h"

enum class LightMode
{
	FLAT_COLOR = 0,
	PHONG_LIGHTNING = 1
};

class Scene
{
private:
	std::shared_ptr<PerspectiveCamera> m_Camera;
	LightMode m_LightMode;
	std::vector<glm::vec3> m_LightSources;

public:
	Scene();

	void SetCamera(std::shared_ptr<PerspectiveCamera> camera);
	void SetLightning(LightMode lightning);
	void AddLightSource(const glm::vec3& position);

	inline std::shared_ptr<PerspectiveCamera> GetCamera() const { return m_Camera; }
	inline LightMode GetLightMode() const { return m_LightMode; }
	inline const std::vector<glm::vec3>& GetLightSources() const { return m_LightSources; }
};