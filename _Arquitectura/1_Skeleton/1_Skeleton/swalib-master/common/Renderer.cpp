#include "Renderer.h"


GLuint texbkg;
void InitRenderer()
{
	texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	
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
void UpdateRenderer()
{
	// Render
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	// Render background
	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
			CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);
		}
	}

	// Render balls
	size_t numBalls = LogicManager::GetInstance().GetBalls().size();
	for (unsigned int i = 0; i < numBalls; i++) 
	{
		CORE_RenderCenteredSprite(LogicManager::GetInstance().GetBalls()[i].GetPosition(),
			vec2(LogicManager::GetInstance().GetBalls()[i].GetRadius() * 2.f, LogicManager::GetInstance().GetBalls()[i].GetRadius() * 2.f),
			LogicManager::GetInstance().GetBalls()[i].GetTexture());
	}
}
void ExitRenderer()
{
	CORE_UnloadPNG(texbkg);
	
}