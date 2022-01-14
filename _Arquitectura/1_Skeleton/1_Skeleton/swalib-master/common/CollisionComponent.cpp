#include "CollisionComponent.h"
#include "Entity.h"
#include "Messages.h"

void Collider::Init(unsigned int _numArgs, va_list args)
{
	if(_numArgs == 1)
	{
		m_radius = va_arg(args, double);
	}
}


void Collider::Update()
{
	//Check collision
	// Collision detection. ---> Move to Collider Component
	bool collision = false;
	int colliding_ball = -1;
	
	std::vector<Collider*>* pOtherColliders = World::GetInstance()->GetWorldColliders();
	if (!pOtherColliders)
	{
		return;
		assert(0);
	}
	for (size_t j = 0; j < pOtherColliders->size(); j++)
	{
		if ((*pOtherColliders)[j] != this)
		{
			float limit2 = (m_radius + (*pOtherColliders)[j]->GetRadius() * (m_radius + (*pOtherColliders)[j]->GetRadius()));
			if (vlen2(root->GetTransform()->GetPosition() 
				- (*pOtherColliders)[j]->root->GetTransform()->GetPosition()) 
				<= limit2)
			{
				collision = true;
				colliding_ball = j;
				break;
			}
		}
	}

	if (collision)
	{
		//Send collision message
		EntCollisionMsg entityMessage(root, ((*pOtherColliders)[colliding_ball])->root);
	}


	// Rebound on margins.
	if ((root->GetTransform()->GetPosition().x > SCR_WIDTH) || (root->GetTransform()->GetPosition().x < 0))
	{
		//Send collision message
		LimitWorldCollMsg collXMessage(root, false);//
	}
	if ((root->GetTransform()->GetPosition().y > SCR_HEIGHT) || (root->GetTransform()->GetPosition().y < 0))
	{
		//Send collision message
		LimitWorldCollMsg collYMessage(root, true);//
	}
}

void Collider::Exit()
{

}
	


