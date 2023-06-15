#include "Texture.h"
#include "External/stb_image.h"

/**
 * Destructor for the Texture class. Deletes the texture object.
 *
 * @returns None
 */
Texture::Texture()
{
	if (m_TextureID != 0)
		glDeleteTextures(1, &m_TextureID);
}

/**
 * Destructor for the Texture class.
 *
 * @param None
 *
 * @returns None
 */
Texture::~Texture()
{

}

/**
 * Loads a texture from a file path and generates a texture ID.
 *
 * @param path The file path of the texture to be loaded.
 *
 * @returns None
 */
void Texture2D::LoadTexture(const std::string& path)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	GLint width, height, bpp;
	stbi_set_flip_vertically_on_load(true);
	GLubyte* data = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cerr << "[stbi_set_flip_vertically_on_load] : Error opening image in file {Texture.cpp}" << std::endl;
		stbi_image_free(data);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Loads a texture from a set of image files and creates a cube map texture.
 *
 * @param paths A vector of file paths to the images to be used for the cube map.
 *
 * @returns None
 */
void TextureMap::LoadTexture(const std::vector<std::string>& paths)
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GLint width, height, bpp;
	stbi_set_flip_vertically_on_load(false);

	for (GLuint i = 0; i < paths.size(); i++)
	{
		GLubyte* data = stbi_load(paths[i].c_str(), &width, &height, &bpp, 4);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cerr << "[stbi_set_flip_vertically_on_load] : Error opening image cube in file {Texture.cpp}" << std::endl;
			stbi_image_free(data);
		}
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}