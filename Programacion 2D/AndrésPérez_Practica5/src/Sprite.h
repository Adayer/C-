#pragma once
#include <litegfx.h>
#include "vector2.h"

class Collider;

class CSprite
{
public:
	//Tipo de la funcion de Callback
	typedef void(*CallbackFunc)(CSprite&, float);
private:
	CallbackFunc callback;

	const ltex_t* texture;

	int hFrames = 1;
	int vFrames = 1;
	float hSize = 0;
	float vSize = 0;

	vec2 uv0;//Esquina superior izq
	vec2 uv1;//Esquina inferior dcha

	int numFrames = hFrames * vFrames;
	float FPS = 0; 
	int currentFrame;
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

public:
	//Numero frames en horizontal y vertical
	CSprite(const ltex_t* tex,
		int _hframes = 1,
		int _vframes = 1) :
		texture(tex),
		hFrames(_hframes),
		vFrames(_vframes),
		position(100.f, 100.f)
	{}

	void Update(float deltaTime);
	void Draw(); //const;

	//Seteo de puntero a la funcion
	void SetCallback(CallbackFunc func) { callback = func; }

	//Properties
	void* GetUserData() { return data; };
	void SetUserData(void* _data) { data = _data; };

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
	void SetPosition(vec2& _pos) { position = _pos;}

	const vec2& GetScale() const { return scale; }
	void SetScale(vec2& _scale) { scale = _scale; }

	const float GetRotation() const { return rotation; }
	void SetRotation(float& _rotation) { rotation = _rotation; }

	//Tamaño de frame multiplicado por la escala
	vec2 GetSize() const { return scale * vec2(hSize, vSize); }

	const vec2& GetPivot() const { return pivot; }
	void SetPivot(vec2& _pivot) { pivot = _pivot; }

	const int GetHFrames() const { return hFrames; }
	const int GetVFrames() const { return vFrames; }

	const float GetFPS() const { return FPS; }
	void SetFPS(float _FPS) { FPS = _FPS; }
	
	const int GetCurrentFrame() const { return currentFrame; }
	void SetCurrentFrame(int _currentFrame) { currentFrame = _currentFrame; }

};