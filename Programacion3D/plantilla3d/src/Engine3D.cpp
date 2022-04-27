#include "Engine3D.h"

#include <GL/glew.h>

#include "Buffer.h"
#include "Shader.h"
#include "Vertex.h"
#include "State.h"

void Engine3D::Init()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	State::defaultShader = new Shader("data/vertex.glsl", "data/fragment.glsl");
}