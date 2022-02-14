#include "Sprite.h"
#include "Collider.h"

void CSprite::Update(float deltaTime)
{
	elapsedTime += deltaTime;
	float tickTime(1.f / FPS);
	if (elapsedTime >= tickTime)
	{
		//TODO: velocidad al reves
		++currentFrame;
		if (currentFrame >= numFrames)
		{
			currentFrame = 0;
		}
		elapsedTime -= (1.f / FPS);
	}
	if (callback)
	{
		(*callback)(*this, deltaTime);
	}
}

void CSprite::Draw() //const
{
	//FIND UVs
	float width = texture->width;
	float height = texture->height;
	hSize = width / hFrames;
	vSize = height / vFrames;
	
	float currentXFrame = currentFrame % hFrames;
	int currentYFrame = currentFrame / hFrames;
	
	
	uv0.x = (hSize * currentXFrame) / width;
	uv0.y = (vSize * currentYFrame) / height;
	
	uv1.x = (hSize * (currentXFrame + 1.f)) / width;
	uv1.y = (vSize * (currentYFrame + 1.f)) / height;

	lgfx_clearcolorbuffer(red, green, blue);
	lgfx_setblend(blendMode);
	ltex_drawrotsized(texture, 
		position.x, position.y, 
		rotation, 
		pivot.x, pivot.y,
		hSize * scale.x, vSize * scale.y,
		uv0.x, uv0.y, uv1.x, uv1.y);
}