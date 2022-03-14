#include "Background.h"

void Background::Update(float _deltaTime, const vec2& _cameraPos)
{
	float percentageXOffset = (_cameraPos.x - m_bufferCameraPos.x) / m_backgroundTexture->width;
	float percentageYOffset = (_cameraPos.y - m_bufferCameraPos.y) / m_backgroundTexture->height;

	float autoXOffset = 0;
	if (m_scrollSpeed.x != 0)
	{
		autoXOffset = (m_scrollSpeed.x / m_backgroundTexture->width)* _deltaTime;
	}
	u0 = u0 + (percentageXOffset * m_scrollRatio) + autoXOffset;
	u1 = u1 + (percentageXOffset * m_scrollRatio) + autoXOffset;

	float autoYOffset = 0;
	if (m_scrollSpeed.y != 0)
	{
		autoYOffset = (m_scrollSpeed.y / m_backgroundTexture->height) * _deltaTime;

	}
	v0 = v0 + (percentageYOffset * m_scrollRatio) + autoYOffset;
	v1 = v1 + (percentageYOffset * m_scrollRatio) + autoYOffset;
}
void Background::Draw(const vec2& _screenSize, const vec2& _cameraPos)
{
	if (m_backgroundTexture == nullptr)
	{
		return;
	}
	lgfx_setcolor(1.f, 1.f, 1.f, 1.f);
	lgfx_setblend(BLEND_ALPHA);
	ltex_drawrotsized(m_backgroundTexture,
		_cameraPos.x, _cameraPos.y,
		0.f,
		0.f, 0.2f,
		m_backgroundTexture->width * m_numReplicationsX, m_backgroundTexture->height * m_numReplicationsY,
		u0, v0, u1, v1);
	m_bufferCameraPos = _cameraPos;
}