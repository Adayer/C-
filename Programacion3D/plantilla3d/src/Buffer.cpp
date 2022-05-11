#include "Buffer.h"
#include <GL/glew.h>
#include "Vertex.h"

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
void Buffer::Draw(const Shader* _pUsedShader) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_tIDs[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_tIDs[1]);
	
	_pUsedShader->setupAttribs();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);
}
