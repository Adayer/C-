#include "World.h"
#include "Camera.h"
#include <iterator>
#include "Vertex.h"
#include "Model.h"
#include "Mesh.h"
#include "Texture.h"

World::World()
{
}
void World::InitWorld()
{
	Vertex vertices[3] =
	{
		Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(1, 1, 1)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(1, 1, 1)),
		Vertex(glm::vec3(0.5f, -0.5f, 0), glm::vec3(1, 1, 1))
	};
	uint16_t indexes[3] = { 0, 1, 2 };

	//Add camera
	Camera* newCamera = new Camera();
	newCamera->setClearColor(glm::vec3(0, 0, 0));
	newCamera->setViewport(glm::ivec4(0, 0, 800, 600));
	newCamera->setPosition(glm::vec3(0, 0, 6));
	addEntity(newCamera);

	//Add triangles
	Mesh* triangleMesh = new Mesh();
	Buffer* pBuffer = (new Buffer(vertices, indexes, glm::vec3(-3.f, 0.f, 0.f)));
	Material* pMaterialFront = (new Material(Texture::load("front.png")));
	Material* pMaterialBack = (new Material(Texture::load("front.png")));
	triangleMesh->addBuffer(*pBuffer, *pMaterialFront);
	
	Model* newModel = new Model(*triangleMesh);
	newModel->setPosition(glm::vec3(0, 0, 0));
	newModel->setScale(glm::vec3(1, 1, 1));
	newModel->setRotation(glm::vec3(0, 0, 0));
	addEntity(newModel);
	
	newModel = new Model(*triangleMesh);
	newModel->setPosition(glm::vec3(3, 0, 0));
	newModel->setScale(glm::vec3(1, 1, 1));
	newModel->setRotation(glm::vec3(0, 0, 0));
	addEntity(newModel);
	
	newModel = new Model(*triangleMesh);
	newModel->setPosition(glm::vec3(-3, 0, 0));
	newModel->setScale(glm::vec3(1, 1, 1));
	newModel->setRotation(glm::vec3(0, 0, 0));
	addEntity(newModel);
}
void World::update(float deltaTime)
{
	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->update(deltaTime);
	}
}
void World::draw()
{
	m_tCameras[0].prepare();

	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->draw();
	}
}

void World::addEntity(Entity* entity) 
{
	m_tEntities.push_back(entity); 
	const Camera* cameraEntity = dynamic_cast<const Camera*>(entity);
	if (cameraEntity)
	{
		m_tCameras.push_back(*cameraEntity);
	}
}
void World::removeEntity(const Entity* entity)
{
	std::vector<Entity*>::iterator iter;
	for (iter = m_tEntities.begin(); iter != m_tEntities.end(); ++iter)
	{
		if (*iter == entity)
		{
			const Camera* cameraEntity = dynamic_cast<const Camera*>(entity);
			if (cameraEntity)
			{
				m_tCameras.pop_back();
			}
			m_tEntities.erase(iter);
			return;
		}
	}
}