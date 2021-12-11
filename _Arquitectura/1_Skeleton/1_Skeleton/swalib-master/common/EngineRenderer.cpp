#include "EngineRenderer.h"

EngineRenderer* EngineRenderer::instance = nullptr;

void EngineRenderer::InitRenderEngine()
{
	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}

void CSprite::UpdateSpriteRender()
{
	CORE_RenderCenteredSprite(m_position, m_size, m_sprite);
}

void CTileableSprite::UpdateSpriteRender()
{
	for (int i = 0; i <= SCR_WIDTH / m_tileWidth; i++) {
		for (int j = 0; j <= SCR_HEIGHT / m_tileHeight; j++) {
			CORE_RenderCenteredSprite(vec2(i * m_tileWidth + m_tileWidth/2.f, j * m_tileHeight + m_tileHeight/2.f), vec2(m_tileWidth, m_tileHeight), m_sprite);
		}
	}
}