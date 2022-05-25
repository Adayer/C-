#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Light.h"

Material::Material(Texture* _tex, Shader* _shader) : m_pTexture(_tex), m_pShader(_shader)
{

}

void Material::prepare() const
{
	const Shader* cosa = getShader();
	int locMPV = getShader()->getLocation("mvp");
	getShader()->setMatrix(locMPV, State::projectionMatrix * State::viewMatrix * State::modelMatrix);
	m_pTexture->bind();
	
	int locTexSample = getShader()->getLocation("texSampler");
	getShader()->setInt(locTexSample, 0);
	
	int locMV = getShader()->getLocation("mv");
	glm::mat4 mvMatrix = State::viewMatrix * State::modelMatrix;
	getShader()->setMatrix(locMV, mvMatrix);
	
	int locNormalMatrix = getShader()->getLocation("norm_matrix");
	glm::mat4 normalMatrix = glm::inverse(mvMatrix);
	normalMatrix = glm::transpose(normalMatrix);
	getShader()->setMatrix(locNormalMatrix, normalMatrix);
	
	int locGlobalAmbient = getShader()->getLocation("globalAmbient");
	getShader()->setVec3(locGlobalAmbient, State::ambient);
	
	int locNumLights = getShader()->getLocation("numLights");
	getShader()->setInt(locNumLights, State::tLights.size());

	size_t numLights = State::tLights.size();
	for (size_t i = 0; i < numLights; i++)
	{
		State::tLights[i]->prepare(i, getShader());
	}
	
	int locMatAmbient = getShader()->getLocation("material.ambient");
	getShader()->setVec4(locMatAmbient, glm::vec4(m_vColor));
	
	int locMatDiffuse = getShader()->getLocation("material.diffuse");
	getShader()->setVec4(locMatDiffuse, glm::vec4(m_vColor));
	
	int locMatSpecular = getShader()->getLocation("material.specular");
	getShader()->setVec3(locMatSpecular, glm::vec3(m_vColor));

	int locMatShininess = getShader()->getLocation("material.shininess");
	getShader()->setFloat(locMatShininess, m_uShininess);
}
