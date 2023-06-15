#pragma once

//OpenGL Headers
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

/**
 * A struct representing a vertex in 3D space.
 *
 * @param position The position of the vertex in 3D space.
 * @param normal The normal vector of the vertex.
 * @param texture The texture coordinates of the vertex.
 * @param textureID The ID of the texture associated with the vertex.
 */
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
	GLfloat textureID;
};