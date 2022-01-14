#include "Entity.h"

void Entity::Init()
{

}
void Entity::Update()
{
	
}
void Entity::Exit()
{

}

void Entity::MoveLeft()
{
	--m_iCurrentPosition;
}
void Entity::MoveRight()
{
	++m_iCurrentPosition;
}