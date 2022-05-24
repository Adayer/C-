#include "World.h"
#include "Camera.h"
#include <iterator>
#include "Vertex.h"
#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Light.h"

World::World()
{
}
void World::InitWorld()
{
	//Add camera
	Camera* newCamera = new Camera();
	newCamera->setClearColor(glm::vec3(1, 1, 0));
	newCamera->setViewport(glm::ivec4(0, 0, 800, 600));
	newCamera->setPosition(glm::vec3(0, 0, 6));
	addEntity(newCamera);
	
	Mesh* cowboy = Mesh::load("data/gunslinger.obj");
	Model* newModel = new Model(*cowboy);
	newModel->setPosition(glm::vec3(4, 0, -5));
	newModel->setScale(glm::vec3(0.25, 0.25, 0.25));
	newModel->setRotation(glm::vec3(0, 45, 0));
	addEntity(newModel);

	Light* newLight = new Light();
	newLight->setColor(glm::vec3(1.f, 0.f, 0.f));
	newLight->setType(Type::Directional);
	m_tLights.push_back(newLight);

	m_vWorldAmbient = glm::vec3(1.f, 1.f, 1.f);
}
void World::update(float deltaTime)
{
	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->update(deltaTime);
	}
}
void World::draw()
{
	State::ambient = m_vWorldAmbient;
	State::tLights = m_tLights;

	m_tCameras[0]->prepare();

	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->draw();
	}
}

void World::addEntity(Entity* entity) 
{
	m_tEntities.push_back(entity); 
	Camera* cameraEntity = dynamic_cast< Camera*>(entity);
	if (cameraEntity)
	{
		m_tCameras.push_back(cameraEntity);
		return;
	}
	Light* lightEntity = dynamic_cast<Light*>(entity);
	if (lightEntity)
	{
		m_tLights.push_back(lightEntity);
		return;
	}
}
void World::removeEntity(const Entity* entity)
{
	std::vector<Entity*>::iterator iter;
	for (iter = m_tEntities.begin(); iter != m_tEntities.end(); ++iter)
	{
		if (*iter == entity)
		{
			const Camera* cameraEntity = dynamic_cast<const Camera*>(entity);
			if (cameraEntity)
			{
				m_tCameras.pop_back();
			}
			//TO DO: Hacer que esto se haga bien para las cameras y las luces
			m_tEntities.erase(iter);
			return;
		}
	}
}