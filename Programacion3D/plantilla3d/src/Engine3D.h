#pragma once

#include "../lib/glm/gtc/matrix_transform.hpp"
#include <vector>
#include "Buffer.h"

class Shader;

class Vertex;

class Engine3D
{
public:
	void Init();
	void Draw();

private:
	Shader* m_sShaderTriangles;

	glm::mat4 P;
	glm::mat4 V;
	std::vector<Buffer> m_tBuffers;
};