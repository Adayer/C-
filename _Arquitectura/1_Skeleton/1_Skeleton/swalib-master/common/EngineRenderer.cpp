#include "EngineRenderer.h"
#include "SpriteRenderer.h"

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

void EngineRenderer::UpdateRenderer()
{
	//We update the sprites from background to foreground to ensure they are render correctly
	size_t numEntities = m_tBackgroundSprites.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tBackgroundSprites[i]->UpdateRender();
	}

	numEntities = m_tDefaultSprites.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tDefaultSprites[i]->UpdateRender();
	}

	numEntities = m_tForegroundSprites.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tForegroundSprites[i]->UpdateRender();
	}

	// Exchanges the front and back buffers
	SYS_Show();
	SYS_Pump();	// Process Windows messages.
}
