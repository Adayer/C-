#include "Collider.h"
#include <algorithm>
#include <vector>

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
	float xClosest = Clamp(_circlePos.x, _rectPos.x - _rectSize.x, _rectPos.x + _rectSize.x);
	float yClosest = Clamp(_circlePos.y, _rectPos.y - _rectSize.y, _rectPos.y + _rectSize.y);
	
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
		float xOffsetNegative = ((_circlePos.x - _radius) < (_pixelPos.x - _pixelsSize.x / 2.f)) ?
			(_pixelPos.x - _pixelsSize.x / 2.f) : (_circlePos.x - _radius);
		float xOffsetPositive = ((_circlePos.x + _radius) > (_pixelPos.x + _pixelsSize.x / 2.f)) ?
			(_pixelPos.x + _pixelsSize.x / 2.f) : (_circlePos.x + _radius);
		float yOffsetNegative = ((_circlePos.y - _radius) < (_pixelPos.y - _pixelsSize.y / 2.f)) ?
			(_pixelPos.y - _pixelsSize.y / 2.f) : (_circlePos.y - _radius);
		float yOffsetPositive = ((_circlePos.y + _radius) < (_pixelPos.y + _pixelsSize.y / 2.f)) ?
			(_pixelPos.y + _pixelsSize.y / 2.f) : (_circlePos.y + _radius);

		vec2 squareStartPos(xOffsetNegative, yOffsetNegative); //Bottom Left Corner
		vec2 squareEndPos(xOffsetPositive, yOffsetPositive); //Top Right Corner
		float squareXSize(xOffsetPositive - xOffsetNegative); //Base
		float squareYSize(yOffsetPositive - yOffsetNegative); //Altura
		//Centro del cuadrado, me parece lo optimo empezar a buscar desde el centro del cuadrado hacia fuera, 
		//ya que hay areas en las cuales los pixeles no estan dentro del circulo en los bordes del cuadrado
		vec2 centerOfSquare(squareStartPos.x + squareXSize, squareStartPos.y + squareYSize);

		for (unsigned int y = squareYSize / 2.f; y <= squareYSize; ++y)
		{
			for (unsigned int x = squareXSize / 2.f; x <= squareXSize; ++x)
			{
				int xNeg = (squareXSize / 2.f) - x;
				int yNeg = (squareYSize / 2.f) - y;

				vec2 buffer(centerOfSquare.x + x, centerOfSquare.y + y);
				vec2 pixelPosRelativeOffset(buffer - _pixelPos); //Posicion relativa del pixel
				
				int alphaPosPos = ((y * _pixelsSize.x + x) * 4) + 3;// +x, +y
				

				int alphaPosNeg = ((y * _pixelsSize.x + xNeg) * 4) + 3;//-x, +y
				int alphaNegPos = ((yNeg * _pixelsSize.x + x) * 4) + 3;//+x, -y
				int alphaNegNeg = ((yNeg * _pixelsSize.x + xNeg) * 4) + 3;//-x, -y
				if (_pixels[alphaPosPos] != 0 || _pixels[alphaPosNeg] != 0 || _pixels[alphaNegPos] != 0 || _pixels[alphaNegNeg] != 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool Collider::CheckRectRect(const vec2& _pos1, const vec2& _size1, 
	const vec2& _pos2, const vec2& _size2) const
{
	//Rect 1 inside of rect 2
	if (IsBetween(_pos1.x - _size1.x,_pos2.x - _size2.x, _pos2.x + _size2.x) || IsBetween(_pos1.x + _size1.x, _pos2.x - _size2.x, _pos2.x + _size2.x) &&
		IsBetween(_pos1.y - _size1.y, _pos2.y - _size2.y, _pos2.y + _size2.y) || IsBetween(_pos1.y + _size1.y, _pos2.y - _size2.y, _pos2.y + _size2.y))
	{
		return true;
	}
	//Rect 2 inside of rect 1
	else if (IsBetween(_pos2.x - _size2.x, _pos1.x - _size1.x, _pos1.x + _size1.x) || IsBetween(_pos2.x + _size2.x, _pos1.x - _size1.x, _pos1.x + _size1.x) &&
		IsBetween(_pos2.y - _size2.y, _pos1.y - _size1.y, _pos1.y + _size1.y) || IsBetween(_pos2.y + _size2.y, _pos1.y - _size1.y, _pos1.y + _size1.y))
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
		xCrossPossible.push_back(_rectPos.x - _rectSize.x);
		xCrossPossible.push_back(_rectPos.x + _rectSize.x);
		//Pixels possible values
		xCrossPossible.push_back(_pixelPos.x - _pixelsSize.x);
		xCrossPossible.push_back(_pixelPos.x + _pixelsSize.x);
		std::sort(xCrossPossible.begin(), xCrossPossible.end()); //Index 1 & 2 are the good values
		//Min & Max X del punto de corte
		float minX = xCrossPossible[1];
		float maxX = xCrossPossible[2];

		//y values
		std::vector<float> yCrossPossible;
		//RectPossible Values
		yCrossPossible.push_back(_rectPos.y - _rectSize.y);
		yCrossPossible.push_back(_rectPos.y + _rectSize.y);
		//Pixels possible values
		yCrossPossible.push_back(_pixelPos.y - _pixelsSize.y);
		yCrossPossible.push_back(_pixelPos.y + _pixelsSize.y);
		std::sort(yCrossPossible.begin(), yCrossPossible.end()); //Index 1 & 2 are the good values
		//Min & Max Y del punto de corte en valor absoluto de pantalla
		float minY = yCrossPossible[1];
		float maxY = yCrossPossible[2];

		//Puntos de corte finales en valor relativo al centro de los pixeles
		vec2 minCrossing(minX - _pixelsSize.x, minY - _pixelsSize.y);
		vec2 maxCrossing(maxX - _pixelsSize.x, maxY - _pixelsSize.y);

		for (unsigned int y = minCrossing.y; y <= maxCrossing.y; ++y)
		{
			for (unsigned int x = minCrossing.x; x <= maxCrossing.x; ++x)
			{
				int pixelAlpha = ((y * _pixelsSize.x + x) * 4) + 3;
				if (_pixels[pixelAlpha] != 0)
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
		xCrossPossible.push_back(_pos1.x - _size1.x);
		xCrossPossible.push_back(_pos1.x + _size1.x);
		//Pixels possible values
		xCrossPossible.push_back(_pos2.x - _size2.x);
		xCrossPossible.push_back(_pos2.x + _size2.x);
		std::sort(xCrossPossible.begin(), xCrossPossible.end()); //Index 1 & 2 are the good values
		

		//Min & Max X del punto de corte
		float minX = xCrossPossible[1];
		float maxX = xCrossPossible[2];

		//y values
		std::vector<float> yCrossPossible;
		//RectPossible Values
		yCrossPossible.push_back(_pos1.y - _size1.y);
		yCrossPossible.push_back(_pos1.y + _size1.y);
		//Pixels possible values
		yCrossPossible.push_back(_pos2.y - _size2.y);
		yCrossPossible.push_back(_pos2.y + _size2.y);
		std::sort(yCrossPossible.begin(), yCrossPossible.end()); //Index 1 & 2 are the good values

		//Min & Max Y del punto de corte en valor absoluto de pantalla
		float minY = yCrossPossible[1];
		float maxY = yCrossPossible[2];

		//Tamaño en pixeles de la zona overlapeada
		vec2 sizeOfOverlapSquare(maxX - minX, maxY - minY);

		//Pixels1 relative start position of overlap
		vec2 pixels1Start(minX - _size1.x, minY - _size1.y);
		vec2 pixels1End(maxX - _size1.x, maxY - _size1.y);
		
		//Pixels2 relative start position of overlap
		vec2 pixels2Start(minX - _size2.x, minY - _size2.y);
		vec2 pixels2End(maxX - _size2.x, maxY - _size2.y);

		for (unsigned int y = 0; y <= sizeOfOverlapSquare.y; ++y)
		{
			for (unsigned int x = 0; x <= sizeOfOverlapSquare.x; ++x)
			{
				int pixelAlpha1 = (((y + pixels1Start.y) * _size1.x + (x + pixels1Start.x)) * 4) + 3;
				int pixelAlpha2 = (((y + pixels2Start.y) * _size2.x + (x + pixels2Start.x)) * 4) + 3;

				if (_pixels1[pixelAlpha1] != 0 && _pixels2[pixelAlpha2] != 0)
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