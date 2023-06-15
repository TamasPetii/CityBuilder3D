#include "Shape.h"
#include <iostream>

/**
 * Concatenates two vectors of vertices into one vector.
 *
 * @param vertices0 The first vector of vertices to concatenate.
 * @param vertices1 The second vector of vertices to concatenate.
 *
 * @returns None
 */
void Shape::ConcatenateVertices(std::vector<Vertex>& vertices0, std::vector<Vertex> vertices1)
{
	vertices0.insert(vertices0.end(), vertices1.begin(), vertices1.end());
}

/**
 * Concatenates two vectors of indices into one vector.
 *
 * @param indices0 The first vector of indices to concatenate.
 * @param indices1 The second vector of indices to concatenate.
 *
 * @returns None
 */
void Shape::ConcatenateIndices(std::vector<GLuint>& indices0, std::vector<GLuint> indices1)
{
	indices0.insert(indices0.end(), indices1.begin(), indices1.end());
}

/**
 * Computes the normal vector of a plane defined by three points.
 *
 * @param start The starting point of the plane.
 * @param destination1 The first destination point of the plane.
 * @param destination2 The second destination point of the plane.
 *
 * @returns The normal vector of the plane.
 */
glm::vec3 Shape::GenerateNormal(glm::vec3 start, glm::vec3 destination1, glm::vec3 destination2)
{
	return glm::normalize(glm::cross(destination1 - start, destination2 - start));
}

//-----------------------------------------------------------NON-STATIC-----------------------------------------------------------//

/**
 * Binds the vertex array object (VAO) associated with this Shape object.
 *
 * @returns None
 */
void Shape::Bind() const
{
	m_VAO.Bind();
}

/**
 * Unbinds the vertex array object (VAO) associated with the Shape object.
 *
 * @returns None
 */
void Shape::UnBind() const
{
	m_VAO.UnBind();
}

/**
 * Renders the shape using OpenGL.
 *
 * @returns None
 */
void Shape::Render() const
{
	glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr);
}

/**
 * Renders the shape using instanced rendering.
 *
 * This function renders the shape using instanced rendering, which allows for efficient rendering of multiple instances of the same shape.
 * The function uses OpenGL to draw the shape using the specified number of instances.
 *
 * @param None
 *
 * @returns None
 */
void Shape::RenderInstanced() const
{
	glDrawElementsInstanced(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr, m_InstanceCount);
}

/**
 * Attaches dynamic data to the Shape's matrix buffer object (MBO).
 *
 * @param transforms A vector of glm::mat4 matrices to attach to the MBO.
 *
 * @returns None
 */
void Shape::AttachMatricesDynamic(const std::vector<glm::mat4>& transforms)
{
	m_MBO.AttachDataDynamic(transforms);
	m_InstanceCount = static_cast<GLuint>(transforms.size());
}

/**
 * Attaches a vector of transformation matrices to the Shape's Mesh Buffer Object (MBO).
 *
 * @param transforms A vector of transformation matrices to attach to the Shape's MBO.
 *
 * @returns None
 */
void Shape::AttachMatricesSubData(const std::vector<glm::mat4>& transforms)
{
	m_MBO.AttachSubData(transforms); //Only copying data! We don't want to reallocate in every render call!
	m_InstanceCount = static_cast<GLuint>(transforms.size());
}

/**
 * Attaches dynamic data to the Shape object's vertex buffer object.
 *
 * @param numbers A vector of GLfloat values representing the dynamic data to be attached.
 *
 * @returns None
 */
void Shape::AttachNumbersDynamic(const std::vector<GLfloat>& numbers)
{
	m_NBO.AttachDataDynamic(numbers);
}

/**
 * Attaches a vector of GLfloat numbers to the Shape's VBO.
 *
 * @param numbers A vector of GLfloat numbers to attach to the Shape's VBO.
 *
 * @returns None
 */
void Shape::AttachNumbersSubData(const std::vector<GLfloat>& numbers)
{
	m_NBO.AttachSubData(numbers);
}

/**
 * Attaches the shape to the GPU by creating and binding vertex buffer objects (VBOs), index buffer objects (IBOs), 
 * model matrix buffer objects (MBOs), and normal buffer objects (NBOs). It also links the attributes of the VBOs and 
 * MBOs to the vertex array object (VAO).
 *
 * @param vertices A vector of vertices that make up the shape.
 * @param indices A vector of indices that define the order in which the vertices should be rendered.
 * @param buffer_size The size of the buffer for the MBO and NBO.
 *
 * @returns None
 */
void Shape::AttachToGPU(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint buffer_size)
{
	m_IndicesCount = static_cast<GLuint>(indices.size());

	m_VAO.Bind();

	m_VBO.AttachDataStatic(vertices);
	m_IBO.AttachDataStatic(indices);
	m_MBO.AttachDataDynamic(std::vector<glm::mat4>(buffer_size));
	m_NBO.AttachDataDynamic(std::vector<GLfloat>(buffer_size));

	m_VAO.LinkAttribute(m_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
	m_VAO.LinkAttribute(m_VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (const void*)(1 * sizeof(glm::vec3)));
	m_VAO.LinkAttribute(m_VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (const void*)(2 * sizeof(glm::vec3)));
	m_VAO.LinkAttribute(m_VBO, 3, 1, GL_FLOAT, sizeof(Vertex), (const void*)(2 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2)));

	m_VAO.LinkAttributeInstance(m_NBO, 4, 1, GL_FLOAT, sizeof(GLfloat), nullptr);

	m_VAO.LinkAttributeInstance(m_MBO, 5, 4, GL_FLOAT, sizeof(glm::mat4),  nullptr);
	m_VAO.LinkAttributeInstance(m_MBO, 6, 4, GL_FLOAT, sizeof(glm::mat4),  (const void*)(1 * sizeof(glm::vec4)));
	m_VAO.LinkAttributeInstance(m_MBO, 7, 4, GL_FLOAT, sizeof(glm::mat4),  (const void*)(2 * sizeof(glm::vec4)));
	m_VAO.LinkAttributeInstance(m_MBO, 8, 4, GL_FLOAT, sizeof(glm::mat4),  (const void*)(3 * sizeof(glm::vec4)));


	m_VAO.UnBind();
	m_VBO.UnBind();
	m_IBO.UnBind();
	m_MBO.UnBind();
}