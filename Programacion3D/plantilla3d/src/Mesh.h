#pragma once
#include "Buffer.h"
#include "Shader.h"

class Mesh
{
public:
	void addBuffer(const Buffer& buffer, const Shader* shader = nullptr);
	size_t getNumBuffers() const
	{
		return m_tBuffers.size();
	}
	const Buffer* getBuffer(size_t index) const
	{
		if (index < m_tBuffers.size())
		{
			return &m_tBuffers[index];
		}
		return nullptr;
	}
	Buffer* getBuffer(size_t index)
	{
		if (index < (m_tBuffers.size() - 1))
		{
			return &m_tBuffers[index];
		}
		return nullptr;
	}
	void draw() const;
private:
	std::vector<Buffer> m_tBuffers;
};