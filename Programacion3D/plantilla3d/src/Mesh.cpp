#define TINYOBJLOADER_IMPLEMENTATION
#include "Mesh.h"
#include "State.h"
#include "Texture.h"
#include <tiny_obj_loader.h>

Mesh* Mesh::load(const char* filename, const Shader* shader)
{
	Mesh* newMesh = new Mesh();

	//Obj
	tinyobj::attrib_t attrib;
	//Meshes? Buffers?
	std::vector<tinyobj::shape_t> shapes;
	//Materiales de cada mesh
	std::vector<tinyobj::material_t> materials;
	//Errores y warnings
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, "data"))
	{
		return nullptr;
	}

	//for (const auto& shape : shapes) 
	for(unsigned int i = 0; i < shapes.size(); ++i)
	{
		std::string route = "data/";
		std::vector<Vertex> tVertexes;
		std::vector<uint16_t> tIndexes;
		//for (const auto& index : shape.mesh.indices) 
		for(unsigned int y = 0; y < shapes[i].mesh.indices.size(); ++y)
		{
			Vertex* vertexAux = new Vertex();
			vertexAux->vPos.x = attrib.vertices[3 * shapes[i].mesh.indices[y].vertex_index + 0];
			vertexAux->vPos.y = attrib.vertices[3 * shapes[i].mesh.indices[y].vertex_index + 1];
			vertexAux->vPos.z = attrib.vertices[3 * shapes[i].mesh.indices[y].vertex_index + 2];
			vertexAux->vColor.r = 1;
			vertexAux->vColor.g = 1;
			vertexAux->vColor.b = 1;
			vertexAux->vTextureCoord.x = attrib.texcoords[2 *
				shapes[i].mesh.indices[y].texcoord_index + 0];
			vertexAux->vTextureCoord.y = attrib.texcoords[2 *
				shapes[i].mesh.indices[y].texcoord_index + 1];
			tVertexes.push_back(*vertexAux);
			tIndexes.push_back(y);
		}
		int numShapes = shapes.size();
		Buffer* newBuffer = new Buffer(&tVertexes[0], tVertexes.size(), &tIndexes[0], tIndexes.size(), glm::vec3(0, 0, 0));
		
		route = route.append(materials[i].ambient_texname);
		Material* newMaterial = (new Material(Texture::load(route.c_str())));
		newMaterial->setShininess(materials[i].shininess);
		newMaterial->setColor(glm::vec4(materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2], 1));
		newMesh->addBuffer(newBuffer, newMaterial);
	}
	int a = 0;
	return newMesh;
}
void Mesh::addBuffer(Buffer* buffer, Material* material)
{
	m_tBuffers.push_back(buffer);
	m_tMaterials.push_back(material);
}
void Mesh::draw() const
{
	size_t numBuffers = m_tBuffers.size();
	for (size_t i = 0; i < numBuffers; ++i)
	{	
		m_tMaterials[i]->prepare();
		m_tBuffers[i]->Draw(m_tMaterials[i]->getShader());
	}
}