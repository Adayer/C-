#pragma once
#include <litegfx.h>
#include "vector2.h"
#include "Collider.h"

//class Collider;

enum CollisionType
{
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
	COLLISION_PIXELS
};

class CSprite
{
public:
	//Tipo de la funcion de Callback
	typedef void(*CallbackFunc)(CSprite&, float);
private:
	bool hasAnimation = false;

	CallbackFunc callback;

	const ltex_t* texture;

	int hFrames = 1;
	int vFrames = 1;
	float hSize = 0;
	float vSize = 0;
	vec2 forcedSize;

	vec2 uv0;//Esquina superior izq
	vec2 uv1;//Esquina inferior dcha

	int numFrames = hFrames * vFrames;
	float FPS = 0; 
	int currentFrame = 0;
	float elapsedTime = 0;

	void* data;

	lblend_t blendMode;

	float red;
	float green;
	float blue;

	vec2 position;
	vec2 scale;
	float rotation;
	vec2 pivot;

	CollisionType collisionType = CollisionType::COLLISION_NONE;
	Collider* spriteCollider = nullptr;
	

public:
	//Numero frames en horizontal y vertical
	CSprite(const ltex_t* tex,
		CollisionType _type,
		int _hframes = 1,
		int _vframes = 1,
		bool _hasAnim = false);

	void Update(float deltaTime);
	void Draw(); //const;

	//Seteo de puntero a la funcion
	void SetCallback(CallbackFunc func) { callback = func; }

	//Properties
	void* GetUserData() { return data; };
	void SetUserData(void* _data) { data = _data; };
	
	bool GetHasAnimation() { return hasAnimation; };
	void SetHasAnimation(bool _hasAnimation) { hasAnimation = _hasAnimation; };

	const ltex_t* GetTexture() const { return texture; };
	void SetTexture(const ltex_t* _tex, int _hframes = 1, int _vframes = 1)
	{
		texture = _tex;
		hFrames = _hframes;
		vFrames = _vframes;
	};
	lblend_t GetBlendMode() const { return blendMode; }
	void SetBlendMode(lblend_t _blend) { blendMode = _blend; }

	float GetRed() { return red; }
	float GetGreen() { return green; }
	float GetBlue() { return blue; }
	void SetColor(float _red, float _green, float _blue)
	{
		red = _red;
		green = _green;
		blue = _blue;
	}

	const vec2& GetPosition() const { return position; }
	void SetPosition(vec2& _pos) { 
		position = _pos;
		spriteCollider->SetPosition(_pos);
	}

	const vec2& GetScale() const { return scale; }
	void SetScale(vec2& _scale) { scale = _scale; }

	const float GetRotation() const { return rotation; }
	void SetRotation(float& _rotation) { rotation = _rotation; }

	//Tamaño de frame multiplicado por la escala
	vec2 GetSize() const { return scale * vec2(hSize, vSize); }

	const vec2& GetPivot() const { return pivot; }
	void SetPivot(vec2& _pivot) { pivot = _pivot; }
	
	const vec2& GetForcedSize() const { return forcedSize; }
	void SetForcedSize(vec2& _size) { 
		forcedSize = _size; 
		if (collisionType == COLLISION_RECT)
		{
			RectCollider* rectCollider = static_cast<RectCollider*>(spriteCollider);
			rectCollider->SetSize(forcedSize);
		}
	}

	const int GetHFrames() const { return hFrames; }
	const int GetVFrames() const { return vFrames; }

	const float GetFPS() const { return FPS; }
	void SetFPS(float _FPS) { FPS = _FPS; }
	
	const int GetCurrentFrame() const { return currentFrame; }
	void SetCurrentFrame(int _currentFrame) { currentFrame = _currentFrame; }

	//Collision
	void SetCollisionType(CollisionType type) { collisionType = type; }
	CollisionType GetCollisionType() const { return collisionType; }

	const Collider* GetCollider() const { return spriteCollider; }

	bool Collides(const CSprite& other) const;

};