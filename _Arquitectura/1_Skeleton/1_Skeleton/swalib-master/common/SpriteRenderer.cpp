#include "SpriteRenderer.h"
#include "Entity.h"

void SpriteRenderer::Init(unsigned int _numArgs, va_list args)
{
	if(_numArgs == 2)
	{
		m_sprite = va_arg(args, GLuint);
		m_size = va_arg(args, vec2);
	}
	EngineRenderer::GetInstance()->AddSprite(this, RenderLayer::Default );
	//EngineRenderer::GetInstance()->AddSprite(this, );
}

void SpriteRenderer::UpdateRender()
{
	CORE_RenderCenteredSprite(root->GetTransform()->GetPosition(), m_size, m_sprite);
}

void TileableSpriteRenderer::Init(unsigned int _numArgs, va_list args)
{
	if(_numArgs == 4)
	{
		m_sprite = va_arg(args, GLuint);
		m_size = va_arg(args, vec2);

		m_tileWidth = va_arg(args, float);
		m_tileHeight = va_arg(args, float);
	}
}
void TileableSpriteRenderer::UpdateRender()
{
	for (int i = 0; i <= SCR_WIDTH / m_tileWidth; i++) {
		for (int j = 0; j <= SCR_HEIGHT / m_tileHeight; j++) {
			CORE_RenderCenteredSprite(vec2(i * m_tileWidth + m_tileWidth / 2.f, j * m_tileHeight + m_tileHeight / 2.f), vec2(m_tileWidth, m_tileHeight), m_sprite);
		}
	}
}