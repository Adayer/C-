#include "SpriteRenderer.h"
#include "Entity.h"

void SpriteRenderer::Init(unsigned int _numArgs, va_list args)
{
	if(_numArgs == 3)
	{
		m_sprite = va_arg(args, GLuint*);
		m_size = va_arg(args, vec2);
		RenderLayer layer = va_arg(args, RenderLayer);
		EngineRenderer::GetInstance()->AddSprite(this, layer); // RenderLayer::Default
	}
}
void SpriteRenderer::Init(unsigned int _numArgs, ...)
{
	va_list valist;
	va_start(valist, _numArgs);
	Init(_numArgs, valist);
	va_end(valist);
}

void SpriteRenderer::UpdateRender()
{
	CORE_RenderCenteredSprite(root->GetTransform()->GetPosition(), m_size, *m_sprite);
}

void TileableSpriteRenderer::Init(unsigned int _numArgs, va_list args)
{
	if(_numArgs == 5)
	{
		m_sprite = va_arg(args, GLuint*);
		m_size = va_arg(args, vec2);
		RenderLayer layer = va_arg(args, RenderLayer);
		EngineRenderer::GetInstance()->AddSprite(this, layer);

		m_tileWidth = va_arg(args, double);
		m_tileHeight = va_arg(args, double);
	}
}
void TileableSpriteRenderer::Init(unsigned int _numArgs, ...)
{
	va_list valist;
	va_start(valist, _numArgs);
	Init(_numArgs, valist);
	va_end(valist);
}

void TileableSpriteRenderer::UpdateRender()
{
	for (int i = 0; i <= SCR_WIDTH / m_tileWidth; i++) {
		for (int j = 0; j <= SCR_HEIGHT / m_tileHeight; j++) {
			CORE_RenderCenteredSprite(
				vec2(i * m_tileWidth + m_tileWidth / 2.f, j * m_tileHeight + m_tileHeight / 2.f), 
				vec2(m_tileWidth, m_tileHeight),
				*m_sprite);
		}
	}
}