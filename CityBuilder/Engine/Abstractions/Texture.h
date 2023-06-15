#pragma once

//OpenGL Header Files
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

//Standard Header Files
#include <string>
#include <iostream>
#include <vector>

/**
 * A base class for textures.
 */
class Texture 
{
public:
	Texture();
	~Texture();

	virtual void LoadTexture(const std::string& path) {};
	virtual void LoadTexture(const std::vector<std::string>& path) {};
	virtual inline bool IsTexture2D() const { return false; }
	virtual inline bool IsTextureMap() const { return false; }
	//Getter
	inline GLuint Get_TextureID() const { return m_TextureID; }
protected:
	GLuint m_TextureID = 0;
};

/**
 * A class representing a 2D texture.
 */
class Texture2D  : public Texture
{
public:
	inline bool IsTexture2D() const override { return true; }
	void LoadTexture(const std::string& path) override;
};

/**
 * A class representing a texture map that inherits from the Texture class.
 */
class TextureMap : public Texture
{
public:
	inline bool IsTextureMap() const override { return true; }
	void LoadTexture(const std::vector<std::string>& path) override;
};
