#include "Background.h"

void Background::Update(float _deltaTime)
{

}
void Background::Draw(const vec2& _screenSize)
{
	if (m_backgroundTexture == nullptr)
	{
		return;
	}
	lgfx_setcolor(1.f, 1.f, 1.f, 1.f);
	lgfx_setblend(BLEND_ALPHA);
	ltex_drawrotsized(m_backgroundTexture,
		0.f,0.f,
		0.f,
		0.f, 0.f,
		m_backgroundTexture->width * 4.f, m_backgroundTexture->height * 4.f,
		0.f, 0.f, 4.f, 4.f);
}