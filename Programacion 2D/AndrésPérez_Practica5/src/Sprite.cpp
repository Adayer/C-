#include "Sprite.h"
#include "Collider.h"


CSprite::CSprite(const ltex_t* tex, CollisionType _type, int _hframes, int _vframes, bool _hasAnim) :
	texture(tex),
	hFrames(_hframes),
	vFrames(_vframes),
	position(100.f, 100.f),
	hasAnimation(_hasAnim),
	collisionType(_type)
{
	switch (collisionType)
	{
	case CollisionType::COLLISION_CIRCLE:
	{
		spriteCollider = new CircleCollider(position, texture->width / 2.f);
		break;
	}
	case CollisionType::COLLISION_RECT:
	{
		spriteCollider = new RectCollider(position, vec2(texture->width, texture->height));
		break;
	}
	case CollisionType::COLLISION_PIXELS:
	{
		unsigned char* pixelsArray = new unsigned char[texture->width * texture->height* 4];
		ltex_getpixels(tex,pixelsArray);
		spriteCollider = new PixelsCollider(position, vec2(texture->width, texture->height), pixelsArray);
		break;
	}
	default:
		break;
	}
}


bool CSprite::Collides(const CSprite& other) const
{
	return spriteCollider->Collides(*(other.GetCollider()));
}

void CSprite::Update(float deltaTime)
{
	if (hasAnimation)
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

	lgfx_setcolor(red, green, blue, 1.f);
	lgfx_setblend(blendMode);
	ltex_drawrotsized(texture, 
		position.x, position.y, 
		rotation, 
		pivot.x, pivot.y,
		hSize * scale.x, vSize * scale.y,
		uv0.x, uv0.y, uv1.x, uv1.y);

	spriteCollider->SetPosition(position);

}