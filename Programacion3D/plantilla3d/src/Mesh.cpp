#include "Mesh.h"
#include "State.h"

Mesh* Mesh::load(const char* filename, const Shader* shader)
{
	return nullptr;
}
void Mesh::addBuffer(Buffer* buffer, Material* material)
{
	if (m_tBuffers.size() == 0)
	{
		m_tBuffers.reserve(2);
	}
	m_tBuffers.push_back(buffer);
	m_tMaterials.push_back(material);
}
void Mesh::draw() const
{
	size_t numBuffers = m_tBuffers.size();
	for (size_t i = 0; i < numBuffers; ++i)
	{	
		m_tMaterials[i]->prepare();
		m_tBuffers[i]->Draw(m_tMaterials[i]->getShader());
	}
}