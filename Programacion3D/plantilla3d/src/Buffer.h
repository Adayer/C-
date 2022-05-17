#pragma once
#include "State.h"
#include <glm.hpp>
#include "Vertex.h"
#include <vector>

class Shader;
//class Vertex;

class Buffer
{
public:
	Buffer() {}
	Buffer(const Vertex* _tVertex,int _iNumVertexes,const uint16_t* _tIndexes, int _iNumIndexes, glm::vec3 _vPos);
	~Buffer();
	void Draw(const Shader* _pUsedShader) const;

	void SetPosition(glm::vec3 _vPos) { m_vPos = _vPos; }
	glm::vec3 GetPosition() { return m_vPos; }

	void SetRotation(float _fRot) { m_fRot = _fRot; }
	float GetRotation() { return m_fRot; }

private:
	uint32_t m_tIDs[2];
	int m_iNumIndexes = 0;
	int m_iNumVertexes = 0;

	glm::vec3 m_vPos;
	float m_fRot;
};