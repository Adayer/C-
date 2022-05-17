#include "Mesh.h"
#include "State.h"
#include "Texture.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Mesh* Mesh::load(const char* filename, const Shader* shader)
{
	Mesh* newMesh = new Mesh();
	std::string route = "data/";
	//Obj
	tinyobj::attrib_t attrib;
	//Meshes? Buffers?
	std::vector<tinyobj::shape_t> shapes;
	//Materiales de cada mesh
	std::vector<tinyobj::material_t> materials;
	//Errores y warnings
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename))
	{
		return nullptr;
	}

	//for (const auto& shape : shapes) 
	for(unsigned int i = 0; i < shapes.size(); ++i)
	{
		Vertex* vertexes = new Vertex[shapes.size()];
		uint16_t* indexes = new uint16_t[shapes.size()];
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
			vertexes[y] = *vertexAux;
			indexes[y] = y;
		}
		int numShapes = shapes.size();
		Buffer* newBuffer = new Buffer(vertexes, numShapes, indexes, numShapes, glm::vec3(0, 0, 0));
		Material* newMaterial = (new Material(Texture::load(route.append(materials[i].ambient_texname).c_str())));
		newMesh->addBuffer(newBuffer, newMaterial);
	}
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