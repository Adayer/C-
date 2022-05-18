#pragma once
#include <glm.hpp>

struct Vertex
{
	Vertex(glm::vec3 _vPos = glm::vec3(0,0,0), 
		glm::vec3 _vNormal= glm::vec3(0, 0, 0),
		glm::vec3 _vColor = glm::vec3(0, 0, 0),
		glm::vec2 _TextureCoord = glm::vec2(0, 0)) :
		vPos(_vPos), 
		vNormal(_vNormal),
		vColor(_vColor),
		vTextureCoord(_TextureCoord)
	{
	}
	glm::vec3 vPos;
	glm::vec3 vNormal;
	glm::vec3 vColor;
	glm::vec2 vTextureCoord;
}; 