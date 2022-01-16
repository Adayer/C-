#pragma once
#include "vector2d.h"
#include "Component.h"
#include "InputManager.h"
#include "SpriteRenderer.h"

class PlayerComponent : public Component
{
private:
	vec2 m_vPlayerInitPosition;
	float m_fPlayerSpeed;
	int m_iMaxLives;
	int m_iCurrentLives;

	//Life variables
	std::vector<SpriteRenderer*> m_tLivesSprites;
	GLuint* m_fullLifeSprite;
	GLuint* m_emptyLifeSprite;

public:
	PlayerComponent(Entity* _root) :
		Component(_root),
		m_vPlayerInitPosition(0, 0),
		m_fPlayerSpeed(0),
		m_iMaxLives(0),
		m_iCurrentLives(m_iMaxLives),
		m_fullLifeSprite(nullptr),
		m_emptyLifeSprite(nullptr)
	{

	};

	//5 args =  vec2 initPos, int maxLives, float speed, GLuint* fullSprite, GLuint* emptySprite
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Init(unsigned int _numArgs, ...) override;
	virtual void Init() override {}
	virtual void Update() override;
	virtual void Exit() override; //No implementation

	virtual void RecieveMessage(Message* _message, Message::MessageType _typeOfMessage) override;

	void OnCollisionEnter();

	//Movement
	void MoveLeft();
	void MoveRight();

	//Adds reference to sprite that renders hearts
	void AddLifeSpriteReference(SpriteRenderer* _newSprite) { m_tLivesSprites.push_back(_newSprite); }
};
