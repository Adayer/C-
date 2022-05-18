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
	const glm::vec4& getColor() const { return m_vColor; }
	void setColor(const glm::vec4& color) { m_vColor = color; }
	uint8_t getShininess() const { return m_uShininess; }
	void setShininess(uint8_t shininess) { m_uShininess = shininess; }
	
	void prepare() const;


private: 
	Shader* m_pShader = nullptr;
	Texture* m_pTexture = nullptr;
	glm::vec4 m_vColor;
	uint8_t m_uShininess;
};