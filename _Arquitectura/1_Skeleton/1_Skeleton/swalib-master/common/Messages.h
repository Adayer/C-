#pragma once
class Entity;
class Message
{
public:
	enum class MessageType
	{
		Invalid = -1,
		EntCollision,
		WorldLimit,
		Count
	};
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

class LimitWorldCollMsg : public CollisionMsg
{
	Entity* ball = nullptr;
	bool yAxisCollision = false;
public:
	LimitWorldCollMsg(Entity* _ball, bool _yAxis);
	Entity* GetBall() const { return ball; }
	bool GetYAxis() { return yAxisCollision; }
};