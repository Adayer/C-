#pragma once
#include "State.h"

class Shader;
class Texture;

class Material
{
public:
	Material(Texture* _tex = nullptr, Shader* shader = nullptr);
	
	const Shader* getShader() const { 
		if (m_pShader)
			return m_pShader;
		else
			return State::defaultShader;
	}
	Shader* getShader() {
		if (m_pShader)
			return m_pShader;
		else
			return State::defaultShader;
	}
	void setShader(Shader* _pShader) { m_pShader = _pShader; }

	const Texture* getTexture() const { return m_pTexture; }
	void setTexture(Texture* _pTex) { m_pTexture = _pTex; }
	void prepare() const;

private: 
	Shader* m_pShader = nullptr;
	Texture* m_pTexture = nullptr;
};