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

void Scene::SetGlobalLight(const glm::vec3& direction, float intensity, const glm::vec3& diffuseColor, const glm::vec3& specColor)
{
	m_GlobalLight = std::make_shared<Light>(glm::normalize(direction), intensity);
	m_GlobalLight->SetDiffuseColor(diffuseColor);
	m_GlobalLight->SetSpecularColor(specColor);
}

void Scene::AddPointLight(std::shared_ptr<Light> light)
{
	m_PointLights.push_back(light);
}
