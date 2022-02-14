#include "Collider.h"

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
	if (_circlePos.x > (_rectPos.x + _rectSize.x / 2.f))
	{
		if (_circlePos.y > (_rectPos.y + _rectSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_rectPos.x + _rectSize.x / 2.f, _rectPos.y + _rectSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else if (_circlePos.y < (_rectPos.y + _rectSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_rectPos.x + _rectSize.x / 2.f, _rectPos.y - _rectSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else
		{
			if (Distance(_circlePos, vec2(_rectPos.x + _rectSize.x / 2.f, _rectPos.y)) <= _radius)
			{
				return true;
			}
		}
	}
	else if (_circlePos.x < (_rectPos.x + _rectSize.x / 2.f))
	{
		if (_circlePos.y > (_rectPos.y + _rectSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_rectPos.x - _rectSize.x / 2.f, _rectPos.y + _rectSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else if (_circlePos.y < (_rectPos.y + _rectSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_rectPos.x - _rectSize.x / 2.f, _rectPos.y - _rectSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else
		{
			if (Distance(_circlePos, vec2(_rectPos.x - _rectSize.x / 2.f, _rectPos.y)) <= _radius)
			{
				return true;
			}
		}
	}
	else
	{
		if (_circlePos.y > (_rectPos.y + _rectSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_rectPos.x, _rectPos.y + _rectSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else if (_circlePos.y < (_rectPos.y + _rectSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_rectPos.x, _rectPos.y -_rectSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}
bool Collider::CheckCirclePixels(const vec2& _circlePos, float _radius,
	const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const
{
	if (_circlePos.x > (_pixelPos.x + _pixelsSize.x / 2.f))
	{
		if (_circlePos.y > (_pixelPos.y + _pixelsSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_pixelPos.x + _pixelsSize.x / 2.f, _pixelPos.y + _pixelsSize.y / 2.f)) <= _radius)
			{
				int i = 0; 
				vec2 crossY(_pixelPos.x + _pixelsSize.x / 2.f, _pixelPos.y);
				while (true)
				{
					if (Distance(crossY + vec2(0.f, i), _circlePos) < _radius)
					{
						crossY = crossY + vec2(0.f, i);
						break;
					}
					++i;
				};
				
				i = 0;
				vec2 crossX(_pixelPos.x, _pixelPos.y + _pixelsSize.y / 2.f);
				while (true)
				{
					if (Distance(crossX + vec2(i, 0.f), _circlePos) < _radius)
					{
						crossX = crossX + vec2(i, 0.f);
						break;
					}
					++i;
				};

				float xPixelStart = (crossX.x - _pixelPos.x) + _pixelsSize.x / 2.f;
				float yPixelEnd= _pixelsSize.y / 2.f - crossY.y;

				for (int i = 0; i <= yPixelEnd; ++i)
				{
					for (int j = xPixelStart; j < _pixelsSize.x; ++j)
					{
						int pixelAlpha = ((i * _pixelsSize.x + j) * 4) - 1;
					}
				}

				return false;
			}
		}
		else if (_circlePos.y < (_pixelPos.y + _pixelsSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_pixelPos.x + _pixelsSize.x / 2.f, _pixelPos.y - _pixelsSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else
		{
			if (Distance(_circlePos, vec2(_pixelPos.x + _pixelsSize.x / 2.f, _pixelPos.y)) <= _radius)
			{
				return true;
			}
		}
	}
	else if (_circlePos.x < (_pixelPos.x + _pixelsSize.x / 2.f))
	{
		if (_circlePos.y > (_pixelPos.y + _pixelsSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_pixelPos.x - _pixelsSize.x / 2.f, _pixelPos.y + _pixelsSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else if (_circlePos.y < (_pixelPos.y + _pixelsSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_pixelPos.x - _pixelsSize.x / 2.f, _pixelPos.y - _pixelsSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else
		{
			if (Distance(_circlePos, vec2(_pixelPos.x - _pixelsSize.x / 2.f, _pixelPos.y)) <= _radius)
			{
				return true;
			}
		}
	}
	else
	{
		if (_circlePos.y > (_pixelPos.y + _pixelsSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_pixelPos.x, _pixelPos.y + _pixelsSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else if (_circlePos.y < (_pixelPos.y + _pixelsSize.y / 2.f))
		{
			if (Distance(_circlePos, vec2(_pixelPos.x, _pixelPos.y - _pixelsSize.y / 2.f)) <= _radius)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}

	return false;
}
bool Collider::CheckRectRect(const vec2& _pos1, const vec2& _size1, 
	const vec2& _pos2, const vec2& _size2) const
{
	if ((_pos1.x < (_pos2.x + _size2.x / 2.f) && _pos1.x >(_pos2.x + _size2.x / 2.f) && 
		_pos1.y < (_pos2.y + _size2.y / 2.f) && _pos1.y >(_pos2.y + _size2.y / 2.f))
		||
		(_pos2.x < (_pos1.x + _size1.x / 2.f) && _pos2.x >(_pos1.x + _size1.x / 2.f) &&
			_pos2.y < (_pos1.y + _size1.y / 2.f) && _pos2.y >(_pos1.y + _size1.y / 2.f)))

	{
		return true;
	}

	return false;
}
bool Collider::CheckRectPixels(const vec2& _rectPos, const vec2& _rectSize, 
	const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const
{
	return false;
}
bool Collider::CheckPixelsPixels(const vec2& _pos1, const vec2& _size1, const uint8_t* _pixels1,
	const vec2& _pos2, const vec2& _size2, const uint8_t* _pixels2) const
{
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