#include "Messages.h"
#include "Entity.h"

EntCollisionMsg::EntCollisionMsg(Entity* _a, Entity* _b) :
	ballA(_a),
	ballB(_b)
{
	ballA->SendMessage(this, MessageType::EntCollision);
	ballB->SendMessage(this, MessageType::EntCollision);
}

LimitWorldCollMsg::LimitWorldCollMsg(Entity* _ball, bool _yAxis) :
	ball(_ball),
	yAxisCollision(_yAxis)
{
	ball->SendMessage(this, MessageType::WorldLimit);
}