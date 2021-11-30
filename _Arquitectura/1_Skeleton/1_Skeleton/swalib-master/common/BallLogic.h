#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "vector2d.h"
#include "font.h"

void InitBalls(GLuint texture);
void UpdateBalls(const double& deltaTime);
void ExitBall(GLuint texture);

struct Ball	// Info Ball
{
	vec2   pos;	// Position.
	vec2   vel;	// Velocity.
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float  radius;	// Radius.

	Ball() :
		pos(0.0f),
		vel(0.0f),
		gfx(0),
		radius(0.0f)
	{}
};

const unsigned int NUM_BALLS = 10;	// Max. num balls.
const float MAX_BALL_SPEED = 40.f;	// Max vel. of ball. (pixels/?).

typedef Ball tBall[NUM_BALLS];