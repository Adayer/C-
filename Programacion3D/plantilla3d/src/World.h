#pragma once
#include <vector>
#include "Entity.h"
class Camera;
class Light;

class World
{
public:
	World();
	void InitWorld();
	void addEntity(Entity* entity);
	void removeEntity(const Entity* entity);
	size_t getNumEntities() const { return m_tEntities.size(); }
	const Entity* getEntity(size_t index) const 
	{
		if (index < m_tEntities.size())
		{
			m_tEntities[index];
		}
		return nullptr;
	}
	Entity* getEntity(size_t index)
	{
		if (index < m_tEntities.size())
		{
			m_tEntities[index];
		}
		return nullptr;
	}
	Camera* getMainCamera() 
	{
		if (m_tCameras.size() > 0) { return m_tCameras[0]; } 
		else { return nullptr; }
	}
	void update(float deltaTime);
	void draw();

	const glm::vec3& getAmbient() const { return m_vWorldAmbient; }
	void setAmbient(const glm::vec3& ambient) { m_vWorldAmbient = ambient; }

private:
	std::vector<Entity*> m_tEntities;
	std::vector<Camera*> m_tCameras;
	std::vector<Light*> m_tLights;

	glm::vec3 m_vWorldAmbient;
};