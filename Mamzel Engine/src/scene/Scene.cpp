#include "Scene.h"

Scene::Scene()
	:m_Camera(nullptr), m_LightMode(LightMode::FLAT_COLOR)
{

}

Scene::~Scene()
{
	m_Camera = nullptr;
	m_PointLights.clear();
	m_DirectionalLight = nullptr;
}

void Scene::SetCamera(std::shared_ptr<PerspectiveCamera>& camera)
{
	m_Camera = camera;
}

void Scene::SetLightning(LightMode lightning)
{
	m_LightMode = lightning;
}

void Scene::SetDirectionalLight(std::shared_ptr<DirectionalLight>& light)
{
	m_DirectionalLight = light;
}

void Scene::SetDirectionalLight(const DirectionalLight& light)
{
	m_DirectionalLight = std::make_shared<DirectionalLight>(light);
}

void Scene::AddPointLight(std::shared_ptr<PointLight>& light)
{
	m_PointLights.push_back(light);
}

void Scene::AddPointLight(const PointLight& light)
{
	m_PointLights.push_back(std::make_shared<PointLight>(light));
}
