#pragma once
#include "vector2.h"
#include "glfw3.h"

class Collider
{
protected:
	vec2 m_currentPos;
public:
	virtual bool Collides(const Collider& _other) const = 0;

	vec2 GetPosition() const { return m_currentPos; }
	void SetPosition(vec2 _pos) { m_currentPos = _pos; }

	virtual bool Collides(const vec2& _circlePos, float _radius) const = 0;
	virtual bool Collides(const vec2& _rectPos, const vec2& _rectSize) const = 0;
	virtual bool Collides(const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const = 0;

protected:
	bool CheckCircleCircle(const vec2& _pos1, float _radius1, const vec2& _pos2, float _radius2) const; 
	bool CheckCircleRect(const vec2& _circlePos, float _radius, const vec2& _rectPos, const vec2& _rectSize) const;
	bool CheckCirclePixels(const vec2& _circlePos, float _radius, const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const;
	bool CheckRectRect(const vec2& _pos1, const vec2& _size1, const vec2& _pos2, const vec2& _size2) const;
	bool CheckRectPixels(const vec2& _rectPos, const vec2& _rectSize, const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const;
	bool CheckPixelsPixels(const vec2& _pos1, const vec2& _size1, const uint8_t* _pixels1, 
		const vec2& _pos2, const vec2& _size2, const uint8_t* _pixels2) const;
};

class CircleCollider : public Collider
{
private:
	float m_radius;

public:
	virtual bool Collides(const Collider& _other) const override;

	float GetRadius() const { return m_radius; }
	void SetSize(float _radius) { m_radius = _radius; }

protected:
	virtual bool Collides(const vec2& _circlePos, float _radius) const override;
	virtual bool Collides(const vec2& _rectPos, const vec2& _rectSize) const override;
	virtual bool Collides(const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const override;
};

class RectCollider : public Collider
{
private:
	vec2 m_size;

public:
	virtual bool Collides(const Collider& _other) const override;

	vec2 GetSize() const { return m_size; }
	void SetSize(vec2 _size) { m_size = _size; }

protected:
	virtual bool Collides(const vec2& _circlePos, float _radius) const override;
	virtual bool Collides(const vec2& _rectPos, const vec2& _rectSize) const override;
	virtual bool Collides(const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const override;
};

class PixelsCollider : public Collider
{
private:
	vec2 m_size;
	uint8_t* m_pixels;
public:
	virtual bool Collides(const Collider& _other) const override;

	vec2 GetSize() const { return m_size; }
	void SetSize(vec2 _size) { m_size = _size; }
	
	uint8_t* GetPixels() const { return m_pixels; }
	void SetSize(uint8_t* _pixels) { m_pixels = _pixels; }

protected:
	virtual bool Collides(const vec2& _circlePos, float _radius) const override;
	virtual bool Collides(const vec2& _rectPos, const vec2& _rectSize) const override;
	virtual bool Collides(const vec2& _pixelPos, const vec2& _pixelsSize, const uint8_t* _pixels) const override;
};