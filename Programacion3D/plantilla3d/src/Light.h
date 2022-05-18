#pragma once
#include <glm.hpp>
class Shader;
enum class Type
{
	Directional,
	Point
};
class Light
{
public:
	Light() : m_eType(Type::Directional), m_vColor(0,0,0)
	{}
	
	Type getType() const { return m_eType; }
	void setType(Type type) { m_eType = type; }
	const glm::vec3& getColor() const { return m_vColor; }
	void setColor(const glm::vec3& color) { m_vColor = color; }
	float getLinearAttenuation() const { return m_fLinearAttenuation; }
	void setLinearAttenuation(float att) { m_fLinearAttenuation = att; }

	void prepare(int index, const Shader* shader) const;
private:
	Type m_eType;
	glm::vec3 m_vColor;
	float m_fLinearAttenuation = 0.f;
};