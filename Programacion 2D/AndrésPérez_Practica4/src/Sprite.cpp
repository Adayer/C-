#include "Sprite.h"



void CSprite::Update(float deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime >= (1.f/FPS))
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
	int currentXFrame = currentFrame % hFrames;
	int currentYFrame = currentFrame % hFrames;

	float u0 = (hSize * currentFrame) / width;
	float v1 = (vSize * currentFrame) / height;
	float v1 = (vSize * currentFrame) / height;


	lgfx_clearcolorbuffer(red, green, blue);
	lgfx_setblend(blendMode);
	ltex_drawrotsized(texture, position.x, position.y, rotation, pivot.x, pivot.y,
		hSize, vSize, uv0.x, uv0.x, uv1.y, uv1.y);
}