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
	Vertex verticesSides[8] =
	{	
		//Left, Top, Back
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,1)),
		//Right, Top, Back
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),
		//Right, Top, Front
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,1)),
		//Left, Top, Front
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),
		//Left, Bot, Back
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,0)),
		//Right, Bot, Back
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(0,0)),
		//Right, Bot, Front
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,0)),
		//Left, Bot, Front
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(0,0))
	};
	Vertex verticesTops[8] =
	{
		//Left, Top, Back
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(0,0)),
		//Right, Top, Back
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,0)),
		//Right, Top, Front
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,1)),
		//Left, Top, Front
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),
		//Left, Bot, Back
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,1)),
		//Right, Bot, Back
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),
		//Right, Bot, Front
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(0,0)),
		//Left, Bot, Front
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,0))
	};
	uint16_t indexesSides[30] = 
	{ 
		0, 1, 5,
		0, 5, 4,

		0, 4, 7,
		0, 7, 3,

		3, 7, 6, 
		3, 6, 2,

		2, 6, 5, 
		2, 5, 1,

		1, 5, 4,
		1, 4, 0
	};
	uint16_t indexesTops[12] = 
	{ 
		0, 3, 2, 0, 2, 1,
		4, 5, 6, 4, 6, 7
	};

	//Add camera
	Camera* newCamera = new Camera();
	newCamera->setClearColor(glm::vec3(1, 1, 0));
	newCamera->setViewport(glm::ivec4(0, 0, 800, 600));
	newCamera->setPosition(glm::vec3(0, 0, 6));
	addEntity(newCamera);

	//Add triangles
	Mesh* triangleMesh = new Mesh();
	//Sides
	Buffer* pBufferSides = (new Buffer(verticesSides, 8, indexesSides,30 ,glm::vec3(-0.5f, 0.f, 0.f)));
	//Tops
	Buffer* pBufferTops = (new Buffer(verticesTops, 8, indexesTops,12, glm::vec3(0.f, 0.f, 0.5f)));
	

	Material* pMaterialFront = (new Material(Texture::load("data/front.png")));
	Material* pMaterialTop = (new Material(Texture::load("data/top.png")));
	triangleMesh->addBuffer(pBufferSides, pMaterialFront);
	triangleMesh->addBuffer(pBufferTops, pMaterialTop);
	
	Model* newModel = new Model(*triangleMesh);
	newModel->setPosition(glm::vec3(0, 0, 0));
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