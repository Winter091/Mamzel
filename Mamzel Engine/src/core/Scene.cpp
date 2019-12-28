#include "Scene.h"

Scene::Scene()
	:m_Camera(nullptr), m_LightMode(LightMode::FLAT_COLOR)
{

}

void Scene::SetCamera(std::shared_ptr<PerspectiveCamera> camera)
{
	m_Camera = camera;
}

void Scene::SetLightning(LightMode lightning)
{
	m_LightMode = lightning;
}

void Scene::AddLightSource(const glm::vec3& position)
{
	m_LightSources.push_back(position);
}
