#pragma once
#include "Buffer.h"
#include "Shader.h"
#include "Material.h"

class Mesh
{
public:
	static Mesh* load(const char* filename, const Shader* shader = nullptr);

	void addBuffer(Buffer* buffer, Material* material);
	void draw() const;

	size_t getNumBuffers() const
	{
		return m_tBuffers.size();
	}
	const Buffer* getBuffer(size_t index) const
	{
		if (index < m_tBuffers.size())
		{
			return m_tBuffers[index];
		}
		return nullptr;
	}
	Buffer* getBuffer(size_t index)
	{
		if (index < (m_tBuffers.size() - 1))
		{
			return m_tBuffers[index];
		}
		return nullptr;
	}

	const Material* getMaterial(size_t index) const
	{
		if (index < m_tMaterials.size())
		{
			return m_tMaterials[index];
		}
		return nullptr;
	}
	Material* getMaterial(size_t index)
	{
		if (index < (m_tMaterials.size() - 1))
		{
			return m_tMaterials[index];
		}
		return nullptr;
	}
	
private:
	std::vector<Buffer*> m_tBuffers;
	std::vector<Material*> m_tMaterials;
};