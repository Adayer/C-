#pragma once
#include <glm.hpp>
#include <vector>
#include <string>

class Shader
{
public:
	Shader(const std::string& _vertexShader, const std::string& _fragmentShader);
	~Shader()
	{

	}
	// Devuelve el identificador de OpenGL del programa
	uint32_t getId() const;
	// Obtiene el mensaje de error generado al compilar o enlazar
	const char* getError() const;
	// Activa el uso de este programa
	void use() const;
	// Activa la escritura de las variables attribute,
	// y especifica su formato
	void setupAttribs() const;
	// Obtiene la localización de una variable uniform
	int getLocation(const char* name) const;
	// Da valor a una variable uniform
	void setInt(int loc, int val) const;
	void setFloat(int loc, float val) const;
	void setVec3(int loc, const glm::vec3& vec) const;
	void setVec4(int loc, const glm::vec4& vec) const;
	void setMatrix(int loc, const glm::mat4& matrix) const;

private:
	
	unsigned int m_vPosLoc;
	unsigned int m_vColorLoc;

	uint32_t m_uID;

	char* m_error;
	std::string readString(const std::string& filename);
};