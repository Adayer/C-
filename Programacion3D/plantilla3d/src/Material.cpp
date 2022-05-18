#include "Material.h"
#include "Shader.h"
#include "Texture.h"

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

	//TO DO: Set uniforms
	//Set ModelView and Normal (traspuesta de la inversa de ModelView)
	//Num lights
	//Color diffuso
	//Shininess
	// Llamar al prepare de cada luz
	//
}
