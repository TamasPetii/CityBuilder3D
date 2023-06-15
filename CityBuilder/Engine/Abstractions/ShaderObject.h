#pragma once

//OpenGL Headers
#include <GLEW/glew.h>

//Standard Headers
#include <string>
#include <fstream>
#include <iostream>
#include <initializer_list>

/**
 * A class representing a shader object.
 */
class ShaderObject
{
public:
	ShaderObject(GLuint shaderType, const std::string& filePath);
	~ShaderObject();

	//Getter
	inline GLuint Get_ShaderID() { return m_ShaderID; }
protected:
	void LoadShader(GLuint shaderType, const std::string& filePath);
private:
	GLuint m_ShaderID;
};

/**
 * A class representing a shader object layout.
 */
class ShaderObjectLayout
{
public:
	ShaderObjectLayout(GLuint layoutLoc, const std::string& layoutName) : m_LayoutLoc(layoutLoc), m_LayoutName(layoutName) {}
	~ShaderObjectLayout() {};

	//Getter
	inline GLuint Get_LayoutLoc() { return m_LayoutLoc; }
	inline const char* Get_LayoutName() { return m_LayoutName.c_str(); }
private:
	GLuint m_LayoutLoc;
	std::string m_LayoutName;
};