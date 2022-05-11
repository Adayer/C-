#pragma once
#include "stb_image.h"
#include <glm.hpp>
#include <GL/glew.h>

class Texture
{
	uint32_t texId;
	glm::ivec2 texSize;
public:
	static Texture* load(const char* filename);
	uint32_t getId() const { return texId; }
	const glm::ivec2& getSize() const { return texSize; }
	void bind() const;
};