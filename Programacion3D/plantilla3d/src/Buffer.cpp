#include "Buffer.h"
#include <GL/glew.h>
#include "Vertex.h"

Buffer::Buffer(const Vertex* _tVertex, int _iNumVertexes, const uint16_t* _tIndexes, int _iNumIndexes, glm::vec3 _vPos) :
	m_vPos (_vPos),
	m_fRot (0), 
	m_iNumVertexes(_iNumVertexes),
	m_iNumIndexes(_iNumIndexes)
{
	glGenBuffers(2, m_tIDs);
	glBindBuffer(GL_ARRAY_BUFFER, m_tIDs[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_tIDs[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _iNumVertexes, _tVertex, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * _iNumIndexes, _tIndexes, GL_STATIC_DRAW);
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
	glDrawElements(GL_TRIANGLES, m_iNumIndexes, GL_UNSIGNED_SHORT, nullptr);
}
