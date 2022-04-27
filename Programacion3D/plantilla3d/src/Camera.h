#pragma once
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera() : Entity()
	{

	}
	const glm::mat4& getProjection() const { return m_mProjection; }
	void setProjection(const glm::mat4& proj) { m_mProjection = proj; }
	const glm::ivec4& getViewport() const { return m_vViewport; }
	void setViewport(const glm::ivec4& vp) { m_vViewport = vp; }
	const glm::vec3& getClearColor() const { return m_vColor; }
	void setClearColor(const glm::vec3& color) { m_vColor = color; }

	void prepare();
protected:
	glm::mat4 m_mProjection;
	glm::ivec4 m_vViewport;
	glm::vec3 m_vColor;
};