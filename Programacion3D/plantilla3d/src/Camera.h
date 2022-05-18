#pragma once
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera() : Entity(), m_vPosition(0,0,6), m_vDirection(0,0,-1)
	{

	}
	const glm::mat4& getProjection() const { return m_mProjection; }
	void setProjection(const glm::mat4& proj) { m_mProjection = proj; }
	const glm::ivec4& getViewport() const { return m_vViewport; }
	void setViewport(const glm::ivec4& vp) { m_vViewport = vp; }
	const glm::vec3& getClearColor() const { return m_vColor; }
	void setClearColor(const glm::vec3& color) { m_vColor = color; }

	void SetCameraDirection(const glm::vec3& _direction) { m_vDirection = _direction; }

	void prepare();

	void Move(const glm::vec3& _offSet);
protected:
	glm::mat4 m_mProjection;
	glm::ivec4 m_vViewport;
	glm::vec3 m_vColor;

	glm::vec3 m_vPosition;
	glm::vec3 m_vDirection;
};