#pragma once
#include <glm.hpp>

struct Vertex
{
	Vertex(glm::vec3 _vPos, glm::vec3 _vColor, glm::vec2 _TextureCoord = glm::vec2(0.f, 0.f)) :
		vPos(_vPos), 
		vColor(_vColor),
		vTextureCoord(_TextureCoord)
	{

	}
	glm::vec3 vPos;
	glm::vec3 vColor;
	glm::vec2 vTextureCoord;
}; 