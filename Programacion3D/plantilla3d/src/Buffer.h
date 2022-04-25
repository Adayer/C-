#pragma once
#include <glm.hpp>
#include "Vertex.h"
#include <vector>

class Shader;
//class Vertex;

class Buffer
{
public:
	Buffer(const Vertex* _tVertex, const uint16_t* _tIndexes, glm::vec3 _vPos);
	~Buffer();
	void Draw(const Shader& shader) const;

	void SetPosition(glm::vec3 _vPos) { m_vPos = _vPos; }
	glm::vec3 GetPosition() { return m_vPos; }

	void SetRotation(float _fRot) { m_fRot = _fRot; }
	float GetRotation() { return m_fRot; }

	void CalculatePMat(const glm::mat4& _P, const glm::mat4& _V, float _deltaTime);
private:


	uint32_t m_tIDs[2];

	float borrar = 0;

	glm::mat4 MVP;
	glm::mat4 M;
	glm::vec3 m_vPos;
	float m_fRot;
};