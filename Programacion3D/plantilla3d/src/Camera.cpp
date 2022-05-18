#include "Camera.h"
#include "State.h"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>

void Camera::prepare()
{
	glViewport(m_vViewport.x, m_vViewport.y, m_vViewport.z, m_vViewport.w);
	glScissor(m_vViewport.x, m_vViewport.y, m_vViewport.z, m_vViewport.w);

	glClearColor(m_vColor.r, m_vColor.g, m_vColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	State::viewMatrix = glm::lookAt(m_vPosition, m_vPosition + m_vDirection, glm::vec3(0, 1, 0));
	State::projectionMatrix = glm::perspective(45.f, 800.f/600.f, 0.1f, 100.f);;
}

void Camera::Move(const glm::vec3& _offset)
{
	m_vPosition += _offset;
}