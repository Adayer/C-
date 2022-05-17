#include "Texture.h"


Texture* Texture::load(const char* filename)
{
	Texture* newTexture = new Texture();
	
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(filename, &newTexture->texSize.x, &newTexture->texSize.y, nullptr, 4);
	glGenTextures(1, &newTexture->texId);
	glBindTexture(GL_TEXTURE_2D, newTexture->texId);

	// Parametros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTexture->texSize.x, newTexture->texSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pixels);

	return newTexture;
}
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, texId);
}