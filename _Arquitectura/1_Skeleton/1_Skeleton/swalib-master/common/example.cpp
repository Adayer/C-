#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "BallLogic.h"
#include "Renderer.h"

//-----------------------------------------------------------------------------
// Logic Info.

//-----------------------------------------------------------------------------
int Main(void)
{
	Init();
	

	//INIT
		//INIT BALLS
		//INIT RENDER
	GLuint texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);


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
  
	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		// Render
		glClear( GL_COLOR_BUFFER_BIT );	// Clear color buffer to preset values.

		// Render backgground
		for (int i = 0; i <= SCR_WIDTH / 128; i++) {
			for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
				CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);
			}
		}

		// Render balls
		for (int i = 0; i < NUM_BALLS; i++) {
			CORE_RenderCenteredSprite(balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);
		}

		// Text
		FONT_DrawString(vec2(SCR_WIDTH/2 - 6*16, 16), "HELLO WORLD!");
   
		// Exchanges the front and back buffers
		SYS_Show();

		// Run balls
				
		SYS_Pump();	// Process Windows messages.
		SYS_Sleep(17);	// To force 60 fps
	}

	// End app.
	// Unload textures.
	
	CORE_UnloadPNG(texbkg);
	FONT_End();

	return 0;
}

void Init() 
{
	InitBalls();
	FONT_Init();	// Characters and symbols inicialization to draw on screen.
}

void Update()
{
	UpdateBalls();
}

void Exit()
{
	ExitBall();
}

