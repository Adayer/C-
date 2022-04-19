#pragma once
#include <glm.hpp>

struct Vertex
{
	Vertex(glm::vec3 _vPos, glm::vec3 _vColor) : 
		vPos(_vPos), 
		vColor(_vColor)
	{

	}
	glm::vec3 vPos;
	glm::vec3 vColor;
}; 