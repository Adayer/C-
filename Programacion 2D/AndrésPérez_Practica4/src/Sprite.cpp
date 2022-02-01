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
	int width = texture->width;
	int height = texture->height;
	hSize = width / hFrames;
	vSize = height / vFrames;
	
	int currentXFrame = currentFrame % hFrames;
	int currentYFrame = currentFrame / hFrames;

	uv0 = vec2((hSize * currentXFrame) / width,(vSize * currentYFrame) / height);
	uv1 = vec2((hSize * (currentXFrame + 1)) / width,(vSize * (currentYFrame + 1)) / height);


	lgfx_clearcolorbuffer(red, green, blue);
	lgfx_setblend(blendMode);
	ltex_drawrotsized(texture, position.x, position.y, rotation, pivot.x, pivot.y,
		hSize, vSize, uv0.x, uv0.y, uv1.x, uv1.y);
}