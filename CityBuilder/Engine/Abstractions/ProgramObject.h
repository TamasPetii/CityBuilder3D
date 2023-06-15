#pragma once

//OpenGL Headers
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

//Standard Headers
#include <initializer_list>

//Engine Headers
#include "ShaderObject.h"
#include "Texture.h"

/**
 * A class representing a shader program object.
 */
class ProgramObject 
{
public:
	ProgramObject();
	~ProgramObject();

	void Bind() const;
	void UnBind() const;

	void Initialize(const std::vector<ShaderObject>& shaders, const std::vector<ShaderObjectLayout>& attribs);

	template<typename T>
	inline void SetUniform(const std::string& name, const T& value);

	template<>
	inline void SetUniform<GLint>(const std::string& name, const GLint& value);

	template<>
	inline void SetUniform<GLfloat>(const std::string& name, const GLfloat& value);

	template<>
	inline void SetUniform<glm::vec2>(const std::string& name, const glm::vec2& value);

	template<>
	inline void SetUniform<glm::vec3>(const std::string& name, const glm::vec3& value);

	template<>
	inline void SetUniform<glm::vec4>(const std::string& name, const glm::vec4& value);

	template<>
	inline void SetUniform<glm::mat4>(const std::string& name, const glm::mat4& value);

	inline void SetUniformTexture(const std::string& name, const GLint sampler, const Texture* texture);

private:
	GLuint m_ProgramID = 0;
};

/**
 * Sets the value of a uniform variable in the program object.
 *
 * @param name The name of the uniform variable.
 * @param value The value to set the uniform variable to.
 *
 * @returns None
 *
 * @throws None
 */
template<typename T>
inline void ProgramObject::SetUniform(const std::string& name, const T& value)
{
	std::cout << "NOT SUPPORTED UNIFORM TYPE" << std::endl;
}

/**
 * Sets the value of a uniform variable in the shader program object.
 *
 * @tparam GLint The data type of the uniform variable.
 * @param name The name of the uniform variable.
 * @param value The value to be set for the uniform variable.
 *
 * @returns None
 */
template<>
inline void ProgramObject::SetUniform<GLint>(const std::string& name, const GLint& value)
{
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

/**
 * Sets a uniform value of type GLfloat in the shader program.
 *
 * @param name The name of the uniform variable in the shader program.
 * @param value The value to be set for the uniform variable.
 *
 * @returns None
 */
template<>
inline void ProgramObject::SetUniform<GLfloat>(const std::string& name, const GLfloat& value)
{
	glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

/**
 * Sets the value of a uniform variable of type glm::vec2 in the shader program.
 *
 * @param name The name of the uniform variable.
 * @param value The value to be set.
 *
 * @returns None
 */
template<>
inline void ProgramObject::SetUniform<glm::vec2>(const std::string& name, const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(m_ProgramID, name.c_str()), value[0], value[1]);
}

/**
 * Sets the value of a uniform variable of type glm::vec3 in the shader program.
 *
 * @param name The name of the uniform variable.
 * @param value The value to set the uniform variable to.
 *
 * @returns None
 */
template<>
inline void ProgramObject::SetUniform<glm::vec3>(const std::string& name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(m_ProgramID, name.c_str()), value[0], value[1], value[2]);
}

/**
 * Sets the value of a uniform variable in the shader program to a 4-component vector.
 *
 * @tparam glm::vec4 The data type of the uniform variable.
 * @param name The name of the uniform variable.
 * @param value The value to set the uniform variable to.
 *
 * @returns None
 */
template<>
inline void ProgramObject::SetUniform<glm::vec4>(const std::string& name, const glm::vec4& value)
{
	glUniform4f(glGetUniformLocation(m_ProgramID, name.c_str()), value[0], value[1], value[2], value[3]);
}

/**
 * Sets the value of a uniform variable in the shader program to a 4x4 matrix.
 *
 * @tparam glm::mat4 The data type of the uniform variable.
 * @param name The name of the uniform variable.
 * @param value The value of the uniform variable.
 *
 * @returns None
 */
template<>
inline void ProgramObject::SetUniform<glm::mat4>(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &(value[0][0]));
}

/**
 * Sets a uniform texture for the program object.
 *
 * @param name The name of the uniform texture.
 * @param sampler The sampler ID of the texture.
 * @param texture The texture object to be set.
 *
 * @returns None
 */
inline void ProgramObject::SetUniformTexture(const std::string& name, const GLint sampler, const Texture* texture)
{
	GLint type = (texture->IsTexture2D() ? GL_TEXTURE_2D : GL_TEXTURE_CUBE_MAP);

	glActiveTexture(GL_TEXTURE0 + sampler);
	glBindTexture(type, texture->Get_TextureID());
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), sampler);
}