#include "Mesh.h"
#include "State.h"

void Mesh::addBuffer(const Buffer& buffer, const Material& material)
{
	m_tBuffers.push_back(buffer);
	m_tMaterials.push_back(material);
}
void Mesh::draw() const
{
	size_t numBuffers = m_tBuffers.size();
	for (size_t i = 0; i < numBuffers; ++i)
	{	
		m_tBuffers[i].Draw(m_tMaterials[i].getShader());
	}
}