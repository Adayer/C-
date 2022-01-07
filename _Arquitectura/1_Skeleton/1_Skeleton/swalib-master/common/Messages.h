#pragma once
class Entity;
class Message
{

};

class CollisionMsg : public Message
{
	
};

class EntCollisionMsg : public CollisionMsg
{
	Entity* ballA = nullptr;
	Entity* ballB = nullptr;
public:
	EntCollisionMsg(Entity* _a, Entity* _b);
	Entity* GetBallA() const { return ballA; }
	Entity* GetBallB() const { return ballB; }
};

class LimitWorldCollMsg : CollisionMsg
{
	Entity* ball = nullptr;
public:
	LimitWorldCollMsg(Entity* _ball);
	Entity* GetBall() const { return ball; }
};