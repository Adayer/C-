#include "Buffer.h"
#include <GL/glew.h>
#include "Vertex.h"
#include "Shader.h"
#include "../lib/glm/gtc/matrix_transform.hpp"

Buffer::Buffer(const Vertex* _tVertex, const uint16_t* _tIndexes, glm::vec3 _vPos) :
	m_vPos (_vPos),
	m_fRot (0)
{
	glGenBuffers(2, m_tIDs);

	glBindBuffer(GL_ARRAY_BUFFER, m_tIDs[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_tIDs[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, _tVertex, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 3, _tIndexes, GL_STATIC_DRAW);
}
Buffer::~Buffer()
{
	const uint32_t tIDs[2] = { m_tIDs[0], m_tIDs[1] };
	glDeleteBuffers(2, tIDs);
}
void Buffer::Draw(const Shader& shader) const
{
	int loc = shader.getLocation("mvp");
	shader.setMatrix(loc, MVP);
	glBindBuffer(GL_ARRAY_BUFFER, m_tIDs[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_tIDs[1]);

	shader.setupAttribs();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);
}

void Buffer::CalculatePMat(const glm::mat4& _P, const glm::mat4& _V, float _deltaTime)
{
	m_fRot += 1 * _deltaTime;
	M = glm::mat4(1.0);
	M = glm::translate(M, m_vPos);
	M = glm::rotate(M, m_fRot, glm::vec3(0.f, 1.f, 0.f));
	M = glm::scale(M, glm::vec3(1.f, 1.f, 1.f));

	MVP = _P * _V * M;
}