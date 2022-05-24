#include "Shader.h"
#include <GL/glew.h>
#include "Vertex.h"
#include <cstring>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
//gl_FragColor = texture2D(texSampler, ftex);

Shader::Shader(const std::string& _vertexFilename, const std::string& _fragmentFilename)
{
	std::string vertexCode = readString(_vertexFilename);
	const char* cVertexShaderSource = vertexCode.c_str();

	//Vertex shader
	int retCode; 
	GLuint sVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertexShader, 1, &cVertexShaderSource, nullptr);
	glCompileShader(sVertexShader);
	glGetShaderiv(sVertexShader, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE)
	{
		char errorLog[1024];
		glGetShaderInfoLog(sVertexShader, sizeof(errorLog), NULL, errorLog);
		m_error = errorLog;
		glDeleteShader(sVertexShader);
		return;
	}

	//Fragment shader
	std::string fragmentCode = readString(_fragmentFilename);
	const char* cFragmentShaderSource = fragmentCode.c_str();
	GLuint sFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragmentShader, 1, &cFragmentShaderSource, nullptr);
	glCompileShader(sFragmentShader);
	glGetShaderiv(sFragmentShader, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE)
	{
		char errorLog[1024];
		glGetShaderInfoLog(sFragmentShader, sizeof(errorLog), NULL, errorLog);
		m_error = errorLog;
		glDeleteShader(sFragmentShader);
		return;
	}

	//Create Program
	m_uID = glCreateProgram();
	glAttachShader(m_uID, sVertexShader);
	glAttachShader(m_uID, sFragmentShader);
	glLinkProgram(m_uID);
	//glDeleteShader(sVertexShader);
	//glDeleteShader(sFragmentShader);
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
	m_vPosLoc = glGetAttribLocation(m_uID, "vpos");
	//m_vColorLoc = glGetAttribLocation(m_uID, "vcolor");
	m_vTextLoc = glGetAttribLocation(m_uID, "vtex");
	m_vVertexNormLoc = glGetAttribLocation(m_uID, "vnormal");

	glUseProgram(m_uID); // TO DO: Cambiar a futuro
}


std::string Shader::readString(const std::string& filename)
{
	std::ifstream istream(filename.c_str(), std::ios_base::binary);
	std::stringstream sstream;
	sstream << istream.rdbuf();
	return sstream.str();
}

int Shader::getLocation(const char* name) const
{
	return glGetUniformLocation(m_uID, name);
}
void Shader::setupAttribs() const
{
	if (m_vPosLoc != -1)
	{
		glEnableVertexAttribArray(m_vPosLoc);
		glVertexAttribPointer(m_vPosLoc, 3, GL_FLOAT, false, sizeof(Vertex),reinterpret_cast<const void*>(offsetof(Vertex, vPos)));
	}
	if (m_vVertexNormLoc != -1)
	{
		glEnableVertexAttribArray(m_vVertexNormLoc);
		glVertexAttribPointer(m_vVertexNormLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, vNormal)));
	}
	/*if (m_vColorLoc != -1)
	{
		glEnableVertexAttribArray(m_vColorLoc);
		glVertexAttribPointer(m_vColorLoc, 3, GL_FLOAT, false, sizeof(Vertex),reinterpret_cast<const void*>(offsetof(Vertex, vColor)));
	}*/
	if (m_vTextLoc != -1)
	{
		glEnableVertexAttribArray(m_vTextLoc);
		glVertexAttribPointer(m_vTextLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, vTextureCoord)));
	}
	if (m_vVertexNormLoc != -1)
	{
		glEnableVertexAttribArray(m_vVertexNormLoc);
		glVertexAttribPointer(m_vVertexNormLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, vNormal)));
	}
}

void Shader::setInt(int loc, int val) const
{
	if (loc != -1)
	{
		glUniform1i(loc, val);
	}
}
void Shader::setFloat(int loc, float val) const
{
	if (loc != -1)
	{
		glUniform1f(loc, val);
	}
}
void Shader::setVec3(int loc, const glm::vec3& vec) const
{
	if (loc != -1)
	{
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}
}
void Shader::setVec4(int loc, const glm::vec4& vec) const
{
	if (loc != -1)
	{
		glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
	}
}
void Shader::setMatrix(int loc, const glm::mat4& matrix) const
{
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, false, value_ptr(matrix));
	}
}