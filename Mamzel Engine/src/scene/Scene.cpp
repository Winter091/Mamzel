#include "Scene.h"

Scene::Scene()
	:m_Camera(nullptr), m_LightMode(LightMode::FLAT_COLOR)
{

}

Scene::~Scene()
{
	m_Camera = nullptr;
	m_PointLights.clear();
	m_GlobalLight = nullptr;
}

void Scene::SetCamera(std::shared_ptr<PerspectiveCamera> camera)
{
	m_Camera = camera;
}

void Scene::SetLightning(LightMode lightning)
{
	m_LightMode = lightning;
}

void Scene::SetGlobalLight(std::shared_ptr<GlobalLight> light)
{
	m_GlobalLight = light;
}

void Scene::SetGlobalLight(const GlobalLight& light)
{
	m_GlobalLight = std::make_shared<GlobalLight>(light);
}

void Scene::AddPointLight(std::shared_ptr<PointLight> light)
{
	m_PointLights.push_back(light);
}

void Scene::AddPointLight(const PointLight& light)
{
	m_PointLights.push_back(std::make_shared<PointLight>(light));
}
