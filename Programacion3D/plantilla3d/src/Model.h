#pragma once

#include "Entity.h"
#include "Mesh.h"

#include <glm.hpp>

class Model : public Entity
{
public:
	Model(const Mesh& mesh) : m_pMesh(&mesh)
	{

	}
	virtual void draw() override;
	virtual void update(float _fDeltaTime) override;
private:
	glm::mat4& CalculateMMat();
	const Mesh* m_pMesh;
};
