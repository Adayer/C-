#include "Collider.h"
#include <algorithm>
#include <vector>
#include "Sprite.h"

float Clamp(float n, float lower, float upper) 
{
	return std::max(lower, std::min(n, upper));
}
bool IsBetween(float _value, float _min, float _max)
{
	if (_min > _max)
	{
		return (_value <= _min && _value >= _max);
	}
	return (_value >= _min && _value <= _max);
}

bool Collider::CheckCircleCircle(const vec2& _pos1, float _radius1,
	const vec2& _pos2, float _radius2) const
{
	if(Distance(_pos1, _pos2) <= (_radius1 + _radius2))
	{
		return true;
	}

	return false;
}
bool Collider::CheckCircleRect(const vec2& _circlePos, float _radius, 
	const vec2& _rectPos, const vec2& _rectSize) const
{
	float xClosest = Clamp(_circlePos.x, _rectPos.x - (_rectSize.x / 2.f), _rectPos.x + (_rectSize.x / 2.f));
	float yClosest = Clamp(_circlePos.y, _rectPos.y - (_rectSize.y / 2.f), _rectPos.y + (_rectSize.y / 2.f));
	
	if (Distance(_circlePos, vec2(xClosest, yClosest)) <= _radius)
	{
		return true;
	}

	return false;
}
bool Collider::CheckCirclePixels(const vec2& _circlePos, float _radius,
	const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const
{
	if (CheckCircleRect(_circlePos, _radius, _pixelPos, _pixelsSize))
	{
		//x values
		std::vector<float> xCrossPossible;
		//CirclePossible Values
		xCrossPossible.push_back(_circlePos.x - _radius);
		xCrossPossible.push_back(_circlePos.x + _radius);
		//Pixels possible values
		xCrossPossible.push_back(_pixelPos.x - (_pixelsSize.x / 2.f));
		xCrossPossible.push_back(_pixelPos.x + (_pixelsSize.x / 2.f));
		std::sort(xCrossPossible.begin(), xCrossPossible.end()); //Index 1 & 2 are the good values
		//Min & Max X del punto de corte
		float minX = xCrossPossible[1];
		float maxX = xCrossPossible[2];

		//y values
		std::vector<float> yCrossPossible;
		//CirclePossible Values
		yCrossPossible.push_back(_circlePos.y - _radius);
		yCrossPossible.push_back(_circlePos.y + _radius);
		//Pixels possible values
		yCrossPossible.push_back(_pixelPos.y - (_pixelsSize.y / 2.f));
		yCrossPossible.push_back(_pixelPos.y + (_pixelsSize.y / 2.f));
		std::sort(yCrossPossible.begin(), yCrossPossible.end()); //Index 1 & 2 are the good values
		//Min & Max Y del punto de corte en valor absoluto de pantalla
		float minY = yCrossPossible[1];
		float maxY = yCrossPossible[2];

		vec2 minCrossing(minX, minY);
		vec2 maxCrossing(maxX, maxY);

		int xMinPixelOffset = minCrossing.x - (_pixelPos.x - (_pixelsSize.x / 2.f));
		int yMinPixelOffset = minCrossing.y - (_pixelPos.y - (_pixelsSize.y / 2.f));

		int xMaxPixelOffset = maxCrossing.x - (_pixelPos.x - (_pixelsSize.x / 2.f));
		int yMaxPixelOffset = maxCrossing.y - (_pixelPos.y - (_pixelsSize.y / 2.f));

		for (unsigned int y = 0; y < (yMaxPixelOffset - yMinPixelOffset); ++y)
		{
			int yPixelIndex = y + yMinPixelOffset;
			for (unsigned int x = 0; x < (xMaxPixelOffset - xMinPixelOffset); ++x)
			{
				int xPixelIndex = x + xMinPixelOffset;

				vec2 pixelWorldPos(minCrossing.x + x, minCrossing.y + y);
				if (Distance(pixelWorldPos, _circlePos) <= _radius)
				{
					int pixelAlphaIndex = ((yPixelIndex * _pixelsSize.x + xPixelIndex) * 4) + 3;
					if (_pixels[pixelAlphaIndex] != 0)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Collider::CheckRectRect(const vec2& _pos1, const vec2& _size1, 
	const vec2& _pos2, const vec2& _size2) const
{
	bool Rect1InsideOfXRect2 = (IsBetween(_pos1.x - (_size1.x / 2.f), _pos2.x - (_size2.x / 2.f), _pos2.x + (_size2.x / 2.f))
		|| IsBetween(_pos1.x + (_size1.x / 2.f), _pos2.x - (_size2.x / 2.f), _pos2.x + (_size2.x / 2.f)));
	bool Rect1InsideOfYRect2 = (IsBetween(_pos1.y - (_size1.y / 2.f), _pos2.y - (_size2.y / 2.f), _pos2.y + (_size2.y / 2.f))
		|| IsBetween(_pos1.y + (_size1.y / 2.f), _pos2.y - (_size2.y / 2.f), _pos2.y + (_size2.y / 2.f)));
	
	bool Rect2InsideOfXRect1 = (IsBetween(_pos2.x - (_size2.x / 2.f), _pos1.x - (_size1.x / 2.f), _pos1.x + (_size1.x / 2.f)) 
		|| IsBetween(_pos2.x + (_size2.x / 2.f), _pos1.x - (_size1.x / 2.f), _pos1.x + (_size1.x / 2.f)));
	bool Rect2InsideOfYRect1 = (IsBetween(_pos2.y - (_size2.y / 2.f), _pos1.y - (_size1.y / 2.f), _pos1.y + (_size1.y / 2.f)) 
		|| IsBetween(_pos2.y + (_size2.y / 2.f), _pos1.y - (_size1.y / 2.f), _pos1.y + (_size1.y / 2.f)));
	//Rect 1 inside of rect 2
	if (Rect1InsideOfXRect2 && Rect1InsideOfYRect2)
	{
		lgfx_setcolor(1.f, 0.f, 0.f, 1.f);
		lgfx_drawrect(_pos1.x, _pos1.y, _size1.x, _size1.y);
		lgfx_setcolor(0.f, 1.f, 0.f, 1.f);
		lgfx_drawrect(_pos2.x, _pos2.y, _size2.x, _size2.y);
		return true;
	}
	////Rect 2 inside of rect 1
	else if (Rect2InsideOfXRect1 && Rect2InsideOfYRect1)
	{
		return true;
	}

	return false;
}
bool Collider::CheckRectPixels(const vec2& _rectPos, const vec2& _rectSize, 
	const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const
{
	if (CheckRectRect(_rectPos, _rectSize, _pixelPos, _pixelsSize))
	{
		//x values
		std::vector<float> xCrossPossible;
		//RectPossible Values
		xCrossPossible.push_back(_rectPos.x - (_rectSize.x / 2.f));
		xCrossPossible.push_back(_rectPos.x + (_rectSize.x / 2.f));
		//Pixels possible values
		xCrossPossible.push_back(_pixelPos.x - (_pixelsSize.x / 2.f));
		xCrossPossible.push_back(_pixelPos.x + (_pixelsSize.x / 2.f));
		std::sort(xCrossPossible.begin(), xCrossPossible.end()); //Index 1 & 2 are the good values
		//Min & Max X del punto de corte
		float minX = xCrossPossible[1];
		float maxX = xCrossPossible[2];

		//y values
		std::vector<float> yCrossPossible;
		//RectPossible Values
		yCrossPossible.push_back(_rectPos.y - (_rectSize.y / 2.f));
		yCrossPossible.push_back(_rectPos.y + (_rectSize.y / 2.f));
		//Pixels possible values
		yCrossPossible.push_back(_pixelPos.y - (_pixelsSize.y / 2.f));
		yCrossPossible.push_back(_pixelPos.y + (_pixelsSize.y / 2.f));
		std::sort(yCrossPossible.begin(), yCrossPossible.end()); //Index 1 & 2 are the good values
		//Min & Max Y del punto de corte en valor absoluto de pantalla
		float minY = yCrossPossible[1];
		float maxY = yCrossPossible[2];

		//Puntos de corte finales en valor relativo al centro de los pixeles
		vec2 minCrossing(minX, minY);
		vec2 maxCrossing(maxX, maxY);

		int xMinPixelOffset = minCrossing.x - (_pixelPos.x - (_pixelsSize.x / 2.f));
		int yMinPixelOffset = minCrossing.y - (_pixelPos.y - (_pixelsSize.y / 2.f));
		
		int xMaxPixelOffset = maxCrossing.x - (_pixelPos.x - (_pixelsSize.x / 2.f));
		int yMaxPixelOffset = maxCrossing.y - (_pixelPos.y - (_pixelsSize.y / 2.f));

		for (unsigned int y = 0; y < (yMaxPixelOffset - yMinPixelOffset); ++y)
		{
			int yPixelIndex = y + yMinPixelOffset;
			for (unsigned int x = 0; x < (xMaxPixelOffset - xMinPixelOffset); ++x)
			{
				int xPixelIndex = x + xMinPixelOffset;
				
				int pixelAlphaIndex = ((yPixelIndex * _pixelsSize.x + xPixelIndex) * 4) + 3;
				if (_pixels[pixelAlphaIndex] != 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool Collider::CheckPixelsPixels(const vec2& _pos1, const vec2& _size1, const uint8_t* _pixels1,
	const vec2& _pos2, const vec2& _size2, const uint8_t* _pixels2) const
{
	if (CheckRectRect(_pos1, _size1, _pos2, _size2))
	{
		//x values
		std::vector<float> xCrossPossible;
		//RectPossible Values
		xCrossPossible.push_back(_pos1.x - (_size1.x / 2.f));
		xCrossPossible.push_back(_pos1.x + (_size1.x / 2.f));
		//Pixels possible values
		xCrossPossible.push_back(_pos2.x - (_size2.x / 2.f));
		xCrossPossible.push_back(_pos2.x + (_size2.x / 2.f));
		std::sort(xCrossPossible.begin(), xCrossPossible.end()); //Index 1 & 2 are the good values
		
		//Min & Max X del punto de corte
		float minX = xCrossPossible[1];
		float maxX = xCrossPossible[2];

		//y values
		std::vector<float> yCrossPossible;
		//RectPossible Values
		yCrossPossible.push_back(_pos1.y - (_size1.y / 2.f));
		yCrossPossible.push_back(_pos1.y + (_size1.y / 2.f));
		//Pixels possible values
		yCrossPossible.push_back(_pos2.y - (_size2.y / 2.f));
		yCrossPossible.push_back(_pos2.y + (_size2.y / 2.f));
		std::sort(yCrossPossible.begin(), yCrossPossible.end()); //Index 1 & 2 are the good values

		//Min & Max Y del punto de corte en valor absoluto de pantalla
		float minY = yCrossPossible[1];
		float maxY = yCrossPossible[2];


		//Puntos de corte finales en valor relativo al centro de los pixeles
		vec2 minCrossing(minX, minY);
		vec2 maxCrossing(maxX, maxY);

		//Pixels 1
		int xMinPixelOffset1 = minCrossing.x - (_pos1.x - (_size1.x / 2.f));
		int yMinPixelOffset1 = minCrossing.y - (_pos1.y - (_size2.y / 2.f));

		int xMaxPixelOffset1 = maxCrossing.x - (_pos1.x - (_size2.x / 2.f));
		int yMaxPixelOffset1 = maxCrossing.y - (_pos1.y - (_size2.y / 2.f));
		
		//Pixels 2
		int xMinPixelOffset2 = minCrossing.x - (_pos2.x - (_size2.x / 2.f));
		int yMinPixelOffset2 = minCrossing.y - (_pos2.y - (_size2.y / 2.f));

		int xMaxPixelOffset2 = maxCrossing.x - (_pos2.x - (_size2.x / 2.f));
		int yMaxPixelOffset2 = maxCrossing.y - (_pos2.y - (_size2.y / 2.f));

		for (unsigned int y = 0; y < (yMaxPixelOffset1 - yMinPixelOffset1); ++y)
		{
			int yPixelIndex1 = y + yMinPixelOffset1;
			int yPixelIndex2 = y + yMinPixelOffset2;
			for (unsigned int x = 0; x < (xMaxPixelOffset1 - xMinPixelOffset1); ++x)
			{
				int xPixelIndex1 = x + xMinPixelOffset1;
				int xPixelIndex2 = x + xMinPixelOffset2;

				int pixelAlphaIndex1 = ((yPixelIndex1 * _size1.x + xPixelIndex1) * 4) + 3;
				int pixelAlphaIndex2 = ((yPixelIndex2 * _size2.x + xPixelIndex2) * 4) + 3;

				if (_pixels1[pixelAlphaIndex1] != 0 && _pixels2[pixelAlphaIndex2] != 0)
				{
					return true;
				}
			}
		}

		
	}
	return false;
}

//Circle
bool CircleCollider::Collides(const Collider& _other) const
{
	return _other.Collides(m_currentPos, m_radius);
}
bool CircleCollider::Collides(const vec2& _circlePos, float _radius) const
{
	return CheckCircleCircle(m_currentPos, m_radius, _circlePos, _radius);
}
bool CircleCollider::Collides(const vec2& _rectPos, const vec2& _rectSize) const
{
	return CheckCircleRect(m_currentPos, m_radius, _rectPos, _rectSize);
}
bool CircleCollider::Collides(const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const
{
	return CheckCirclePixels(m_currentPos, m_radius, _pixelPos, _pixelsSize, _pixels);
}

//Rect
bool RectCollider::Collides(const Collider& _other) const
{
	return _other.Collides(m_currentPos, m_size);
}
bool RectCollider::Collides(const vec2& _circlePos, float _radius) const
{
	return CheckCircleRect(_circlePos, _radius, m_currentPos, m_size);
}
bool RectCollider::Collides(const vec2& _rectPos, const vec2& _rectSize) const
{
	return CheckRectRect(m_currentPos, m_size, _rectPos, _rectSize);
}
bool RectCollider::Collides(const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const
{
	return CheckRectPixels(m_currentPos, m_size, _pixelPos, _pixelsSize, _pixels);
}

//Pixels
bool PixelsCollider::Collides(const Collider& _other) const
{
	return _other.Collides(m_currentPos, m_size, m_pixels);
}

bool PixelsCollider::Collides(const vec2& _circlePos, float _radius) const
{
	return CheckCirclePixels(_circlePos, _radius, m_currentPos, m_size, m_pixels);
}
bool PixelsCollider::Collides(const vec2& _rectPos, const vec2& _rectSize) const
{
	return CheckRectPixels(_rectPos, _rectSize, m_currentPos, m_size, m_pixels);
}
bool PixelsCollider::Collides(const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const
{
	return CheckPixelsPixels(m_currentPos, m_size, m_pixels, _pixelPos, _pixelsSize, _pixels);
}