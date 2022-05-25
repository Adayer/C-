#include "Light.h"
#include "Shader.h"
#include "State.h"
#include <string>

void Light::prepare(int index, const Shader* shader) const
{
	std::string lightName = "light[";
	std::string ambientName = "].ambient";
	std::string diffuseName = "].diffuse";
	std::string specularName = "].specular";
	std::string positionName = "].position";
	std::string indexStr = std::to_string(index);

	//Set up uniform variables in shader
	int locLightAmbient = shader->getLocation
	((lightName + std::to_string(index) + ambientName).c_str());
	shader->setVec4(locLightAmbient, glm::vec4(m_vColor, 0.f));

	int locLightDiffuse = shader->getLocation
	((lightName + std::to_string(index) + diffuseName).c_str());
	shader->setVec4(locLightDiffuse, glm::vec4(m_vColor, 0.f));

	int locLightSpecular = shader->getLocation
	((lightName + std::to_string(index) + specularName).c_str());
	shader->setVec4(locLightSpecular, glm::vec4(m_vColor, 0.f));

	int locMatPos = shader->getLocation
	((lightName + std::to_string(index) + positionName).c_str());
	shader->setVec3(locMatPos, m_vPos);

	int locIsPoint = shader->getLocation("isPointLight");
	int value = m_eType == Type::Point ? 1 : 0;
	shader->setInt(locIsPoint, value);
	
	int locAtt = shader->getLocation("linearAtt");
	shader->setFloat(locAtt, m_fLinearAttenuation);
}
