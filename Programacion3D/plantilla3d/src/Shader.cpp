#include "Shader.h"
#include <GL/glew.h>
#include "Vertex.h"
#include <cstring>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& _vertexFilename, const std::string& _fragmentFilename)
{
	std::string vertexCode = readString(_vertexFilename);
	const char* cVertexShaderSource = vertexCode.c_str();

	//Vertex shader
	int retCode; 
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &cVertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE)
	{
		char errorLog[1024];
		glGetShaderInfoLog(vertexShader, sizeof(errorLog), NULL, errorLog);
		m_error = errorLog;
		glDeleteShader(vertexShader);
		return;
	}

	//Fragment shader
	std::string fragmentCode = readString(_fragmentFilename);
	const char* cFragmentShaderSource = fragmentCode.c_str();
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &cFragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE)
	{
		char errorLog[1024];
		glGetShaderInfoLog(fragmentShader, sizeof(errorLog), NULL, errorLog);
		m_error = errorLog;
		glDeleteShader(fragmentShader);
		return;
	}

	//Create Program
	m_uID = glCreateProgram();
	glAttachShader(m_uID, vertexShader);
	glAttachShader(m_uID, fragmentShader);
	glLinkProgram(m_uID);
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	glGetProgramiv(m_uID, GL_LINK_STATUS, &retCode);

	if (retCode == GL_FALSE)
	{
		char errorLog[1024];
		glGetProgramInfoLog(m_uID, sizeof(errorLog), NULL, errorLog);
		m_error = errorLog;
		glDeleteProgram(m_uID);
		printf("%s", m_error);
		m_uID = 0;
		return;
	}

	//Vertex shader attributes
	glGetAttribLocation(m_uID, "vpos");
	glGetAttribLocation(m_uID, "vcolor");
}

std::string Shader::readString(const std::string& filename)
{
	std::ifstream istream(filename.c_str(), std::ios_base::binary);
	std::stringstream sstream;
	sstream << istream.rdbuf();
	return sstream.str();
}

void Shader::setupAttribs() const
{
	if (m_vPosLoc != -1)
	{
		glEnableVertexAttribArray(m_vPosLoc);
		glVertexAttribPointer(m_vPosLoc, 3, GL_FLOAT, false, sizeof(Vertex),reinterpret_cast<const void*>(offsetof(Vertex, vPos)));
	}
	if (m_vColorLoc != -1)
	{
		glEnableVertexAttribArray(m_vColorLoc);
		glVertexAttribPointer(m_vColorLoc, 3, GL_FLOAT, false, sizeof(Vertex),reinterpret_cast<const void*>(offsetof(Vertex, vColor)));
	}
}

void Shader::setInt(int loc, int val)
{
	if (loc != -1)
	{
		glUniform1i(loc, val);
	}
}
void Shader::setFloat(int loc, float val)
{
	if (loc != -1)
	{
		glUniform1f(loc, val);
	}
}
void Shader::setVec3(int loc, const glm::vec3& vec)
{
	if (loc != -1)
	{
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}
}
void Shader::setVec4(int loc, const glm::vec4& vec)
{
	if (loc != -1)
	{
		glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
	}
}
void Shader::setMatrix(int loc, const glm::mat4& matrix)
{
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, false, value_ptr(matrix));
	}
}