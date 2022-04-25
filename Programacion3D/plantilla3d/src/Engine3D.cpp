#include "Engine3D.h"

#include <GL/glew.h>

#include "Buffer.h"
#include "Shader.h"
#include "Vertex.h"

void Engine3D::Init()
{
	glewInit();
	glViewport(0, 0, 800, 600);
	glScissor(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);


	P = glm::perspective(45.f, 800.f/600.f, 0.1f, 100.f);
	V = glm::lookAt(glm::vec3(0, 0, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	m_sShaderTriangles = new Shader("data/vertex.glsl", "data/fragment.glsl");

	Vertex vertices[3] =
	{
		Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(0.5f, -0.5f, 0), glm::vec3(1, 0, 0))
	};
	uint16_t indexes[3] = { 0, 1, 2 };

	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(-3.f, 0.f, 0.f)));
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(-3.f, 0.f, -3.f)));
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(-3.f, 0.f, -6.f)));
	
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(0.f, 0.f, 0.f)));
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(0.f, 0.f, -3.f)));
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(0.f, 0.f, -6.f)));
	
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(3.f, 0.f, 0.f)));
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(3.f, 0.f, -3.f)));
	m_tBuffers.push_back(new Buffer(vertices, indexes, glm::vec3(3.f, 0.f, -6.f)));
}
void Engine3D::Draw(float _deltaTime)
{
	size_t numBuffer = m_tBuffers.size();
	for (size_t i = 0; i < numBuffer; ++i)
	{
		m_tBuffers[i]->CalculatePMat(P, V, _deltaTime);
		m_tBuffers[i]->Draw(*m_sShaderTriangles);
	}
}