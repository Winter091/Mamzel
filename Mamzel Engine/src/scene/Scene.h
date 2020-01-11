#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../scene/PerspectiveCamera.h"
#include "../renderer/Shader.h"
#include "DirectionalLight.h"
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
	LightMode m_LightMode;

	std::vector<std::shared_ptr<PointLight>> m_PointLights;
	std::shared_ptr<DirectionalLight> m_DirectionalLight;

public:
	Scene();
	~Scene();

	void SetCamera(std::shared_ptr<PerspectiveCamera>& camera);
	void SetLightning(LightMode lightning);

	void SetDirectionalLight(std::shared_ptr<DirectionalLight>& light);
	void SetDirectionalLight(const DirectionalLight& light);

	void AddPointLight(std::shared_ptr<PointLight>& light);
	void AddPointLight(const PointLight& light);

	inline std::shared_ptr<PerspectiveCamera>& GetCamera() { return m_Camera; }
	inline LightMode GetLightMode() const { return m_LightMode; }
	inline const std::vector<std::shared_ptr<PointLight>>& GetPointLights() const { return m_PointLights; }
	inline const std::shared_ptr<DirectionalLight>& GetDirectionalLight() { return m_DirectionalLight; }
};