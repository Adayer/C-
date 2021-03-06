#include "CollisionComponent.h"
#include "Entity.h"
#include "Messages.h"
#include "World.h"

void Collider::Init(unsigned int _numArgs, va_list args)
{
	if(_numArgs == 1)
	{
		m_radius = va_arg(args, double);
		World::GetInstance()->AddCollider(this);
	}
}
void Collider::Init(unsigned int _numArgs, ...)
{
	va_list valist;
	va_start(valist, _numArgs);
	Init(_numArgs, valist);
	va_end(valist);
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
			float limit2 = (m_radius + (*pOtherColliders)[j]->GetRadius());
			vec2 vecDist = root->GetTransform()->GetPosition()
				- (*pOtherColliders)[j]->root->GetTransform()->GetPosition();
			float distBetween = vlen(vecDist);
			distBetween = abs(distBetween);
			if (distBetween <= limit2)
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
	if (((root->GetTransform()->GetPosition().x + m_radius) > (SCR_WIDTH - 13)) || ((root->GetTransform()->GetPosition().x - m_radius) < 13))
	{
		//Send collision message
		LimitWorldCollMsg collXMessage(root, false);//
	}
	if (((root->GetTransform()->GetPosition().y + m_radius) > SCR_HEIGHT - 17) || ((root->GetTransform()->GetPosition().y - m_radius) < 17))
	{
		//Send collision message
		LimitWorldCollMsg collYMessage(root, true);//
	}
}

void Collider::Exit()
{
	World::GetInstance()->RemoveCollider(this);
}
	


