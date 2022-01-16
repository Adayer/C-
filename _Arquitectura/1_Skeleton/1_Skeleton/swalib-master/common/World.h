#pragma once
#include <vector>


#define NUM_BALLS 7
#define BIG_BALL_DIAMETER 64.f
#define BIG_BALL_COL_RADIUS 32.f

class Entity;
class Collider;

class World
{
private:
	World() {};
	static World* instance;

	std::vector<Entity*> entities;
	std::vector<Collider*> colliders;

	std::vector<Entity*> entitiesToRemoveAtEndOfFrame;

	Entity* m_backgroundEntity;

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
	void AddEntity(Entity* _newEntity);
	void RemoveEntity(Entity* _entityToRemove);
	void ClearEntities(); //Counts numberOfEntities to remove
private:
	void ClearEntityFromList(int _numEntsToClear); //Clears first inactive entities from entity vector and calls itself untill there are 0 left
public:
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
	void Update();
	void Exit(); //Pending
};