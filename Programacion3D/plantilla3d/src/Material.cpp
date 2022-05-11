#include "Material.h"
#include "Shader.h"
#include "Texture.h"

Material::Material(Texture* _tex, Shader* _shader) : m_pTexture(_tex), m_pShader(_shader)
{

}

void Material::prepare()
{
	int locMPV = getShader()->getLocation("mvp");
	getShader()->setMatrix(locMPV, State::projectionMatrix * State::viewMatrix * State::modelMatrix);

	int hasTex = m_pTexture ? 1 : 0;
	int locBool = getShader()->getLocation("hasTex");
	getShader()->setInt(locMPV, hasTex);

	m_pTexture->bind();
	int locTexSample = getShader()->getLocation("texSampler");
	getShader()->setInt(locTexSample, getTexture()->getId());
}
