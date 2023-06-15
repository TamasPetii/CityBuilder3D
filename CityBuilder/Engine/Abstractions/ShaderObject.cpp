#include "ShaderObject.h"

/**
 * Constructs a ShaderObject object by loading a shader from a file.
 *
 * @param shaderType The type of shader to load.
 * @param filePath The path to the file containing the shader code.
 *
 * @returns None
 */
ShaderObject::ShaderObject(GLuint shaderType, const std::string& filePath)
{
	LoadShader(shaderType, filePath);
}

/**
 * Destructor for the ShaderObject class.
 * Deletes the shader object from the GPU.
 *
 * @returns None
 */
ShaderObject::~ShaderObject()
{
	glDeleteShader(m_ShaderID);
}

/**
 * Loads a shader from a file and compiles it.
 *
 * @param shaderType The type of shader to be loaded (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
 * @param filePath The path to the file containing the shader source code.
 *
 * @returns None
 */
void ShaderObject::LoadShader(GLuint shaderType, const std::string& filePath)
{
	//Opening the shader file
	std::ifstream f(filePath);
	if (!f.is_open())
	{
		std::cerr << "[std::ifstream] : Cannot open shader in file {ShaderObject.cpp}!" << std::endl;
		exit(1);
	}

	//Process the content of shader file
	std::string line, source;
	while (std::getline(f, line))
	{
		source += line + "\n";
	}

	//Creating a new shader
	m_ShaderID = glCreateShader(shaderType);
	if (m_ShaderID == 0)
	{
		std::cerr << "[glCreateShader] : Error while creating shader. Type: " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " in file {ShaderObject.cpp}" << std::endl;
		exit(1);
	}

	//Attaching the content of shader file
	const GLchar* sourcePointer = source.c_str();
	glShaderSource(m_ShaderID, 1, &sourcePointer, nullptr);
	glCompileShader(m_ShaderID);

	//Check possible shader compile errors
	int result, info_length;
	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &info_length);

	if (result == GL_FALSE)
	{
		char* message = (char*)_malloca(info_length * sizeof(char));

		glGetShaderInfoLog(m_ShaderID, info_length, &info_length, message);
		std::cout << "[glCompileShader] : Error occured while compiling shaders. Type: " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " in file {ShaderObject.cpp}" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(m_ShaderID);
		delete message;
		exit(1);
	}
}
