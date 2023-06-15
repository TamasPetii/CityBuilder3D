#include "ProgramObject.h"

/**
 * Constructor for the ProgramObject class. Creates a new OpenGL program object.
 *
 * @returns None
 */
ProgramObject::ProgramObject()
{
	if (m_ProgramID == 0) m_ProgramID = glCreateProgram();

	//Check Errors
	if (m_ProgramID == -1)
	{
		std::cout << "[glCreateProgram] Error occured while creating new program ID" << std::endl;
		exit(1);
	}
}

/**
 * Destructor for ProgramObject class.
 * Deletes the program object if it exists.
 *
 * @returns None
 */
ProgramObject::~ProgramObject()
{
	if (m_ProgramID != 0) glDeleteProgram(m_ProgramID);
}

/**
 * Binds the program object to the current OpenGL context.
 *
 * @param None
 *
 * @returns None
 */
void ProgramObject::Bind() const
{
	glUseProgram(m_ProgramID);
}

/**
 * Unbinds the current program object.
 *
 * @returns None
 */
void ProgramObject::UnBind() const
{
	glUseProgram(0);
}

/**
 * Initializes the program object with the given shaders and attribute layouts.
 *
 * @param shaders A vector of ShaderObject instances to attach to the program.
 * @param attribs A vector of ShaderObjectLayout instances to bind to the program.
 *
 * @returns None
 */
void ProgramObject::Initialize(const std::vector<ShaderObject>& shaders, const std::vector<ShaderObjectLayout>& attribs)
{
	//At his point {Initializer list <ShaderObjects>} has been already loaded shader files

	//Attach shader to prgoram
	for (ShaderObject s : shaders)
	{
		glAttachShader(m_ProgramID, s.Get_ShaderID());
	}

	//Assigning VAO attributes to shader variables (Must do before linking the program!)
	for (ShaderObjectLayout a : attribs)
	{
		glBindAttribLocation(m_ProgramID, a.Get_LayoutLoc(), a.Get_LayoutName());
	}

	//Linking the program and validating it -> information about the validation in info log
	glLinkProgram(m_ProgramID);
	glValidateProgram(m_ProgramID);

	//Check possible linking errors
	int result, info_length;
	glGetShaderiv(m_ProgramID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_ProgramID, GL_INFO_LOG_LENGTH, &info_length);

	if (result == GL_FALSE)
	{
		char* message = (char*)_malloca(info_length * sizeof(char));

		glGetProgramInfoLog(m_ProgramID, info_length, &info_length, message);
		std::cout << "[glLinkProgram] Error occured while linking the program. ID - " << m_ProgramID << " in file {ProgramObject.cpp}" << std::endl;
		std::cout << message << std::endl;

		delete message;
		exit(1);
	}

	//Unbindig program
	glUseProgram(0);
}