#pragma once
#include <vector>
#include "Entity.h"
class Camera;
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
	
	void update(float deltaTime);
	void draw();
private:
	std::vector<Entity*> m_tEntities;
	std::vector<Camera> m_tCameras;
};