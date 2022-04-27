#pragma once

#include <glm.hpp>

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}

	const glm::vec3& getPosition() const { return m_vPos; }
	void setPosition(const glm::vec3& pos) { m_vPos = pos; }
	const glm::vec3& getRotation() const { return m_vRot; } // puede ser quat
	const void setRotation(const glm::vec3& rot) { m_vRot = rot; } // puede ser quat
	const glm::vec3& getScale() const { return m_vScale; }
	void setScale(const glm::vec3& scale) { m_vScale = scale; }

	void move(const glm::vec3& vec); // ver en las diapositivas

	virtual void update(float deltaTime) {}
	virtual void draw() {}
protected:
	glm::vec3 m_vPos;
	glm::vec3 m_vRot;
	glm::vec3 m_vScale;

};