#pragma once

#include <glm.hpp>
#include "Shader.h"

class Shader;

class State
{
public:
	static Shader* defaultShader;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static glm::mat4 modelMatrix;
};