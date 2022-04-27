#include "Model.h"
#include "State.h"
#include "../lib/glm/gtc/matrix_transform.hpp"

void Model::draw()
{
	State::modelMatrix = CalculateMMat();
	m_pMesh->draw();
}
void Model::update(float _fDeltaTime)
{
	m_vRot.y += _fDeltaTime;
}

glm::mat4& Model::CalculateMMat()
{
	glm::mat4 M = glm::mat4(1.0);
	M = glm::translate(M, m_vPos);
	M = glm::rotate(M, m_vRot.x, glm::vec3(1, 0, 0));
	M = glm::rotate(M, m_vRot.y, glm::vec3(0, 1, 0));
	M = glm::rotate(M, m_vRot.z, glm::vec3(0, 0, 1));
	M = glm::scale(M, m_vScale);

	return M;
}