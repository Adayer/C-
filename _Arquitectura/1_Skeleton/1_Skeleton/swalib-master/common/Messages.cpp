#include "Messages.h"
#include "Entity.h"

EntCollisionMsg::EntCollisionMsg(Entity* _a, Entity* _b) :
	ballA(_a),
	ballB(_b)
{
	ballA->SendMessage(this);
	ballB->SendMessage(this);
}

LimitWorldCollMsg::LimitWorldCollMsg(Entity* _ball) :
	ball(_ball)
{
	ball->SendMessage(this);
}