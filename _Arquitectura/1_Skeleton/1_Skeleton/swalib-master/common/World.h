#pragma once
#include <vector>


#define NUM_BALLS 16

class Entity;
class Collider;

class World
{
private:
	World() {};
	static World* instance;

	std::vector<Entity*> entities;
	std::vector<Collider*> colliders;

public:
	static World* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new World();
		}
		return instance;
	}

	//To assure Logic Manager is not copied or created using a copy
	World(World& other) = delete;
	void operator=(const World&) = delete;

	std::vector<Entity*>* GetWorldEntities() { return &entities; }
	//Entities created are created with new but there is currently no delete
	void AddEntity(Entity* _newEntity)
	{
		if (_newEntity)
		{
			entities.push_back(_newEntity);
		}
	}
	void RemoveEntity(Entity* _entityToRemove);
	
	std::vector<Collider*>* GetWorldColliders() { return &colliders; }
	//Entities created are created with new but there is currently no delete
	void AddCollider(Collider* _newCollider)
	{
		if (_newCollider)
		{
			colliders.push_back(_newCollider);
		}
	}
	void RemoveCollider(Collider* _colliderToRemove);

	void Init(); //Initialize scene
	void Exit(); //Pending
};