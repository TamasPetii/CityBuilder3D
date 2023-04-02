#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

#include "../Abstractions/BufferObject.h"
#include "../Abstractions/VertexArrayObject.h"

class Shape
{
public:
	virtual void CreateBuffers() = 0;

	void Bind() const;
	void UnBind() const;

	void Render() const;
	void RenderInstanced() const;

	void AttachMatrices(const std::vector<glm::mat4>& transforms);

	static void ConcatenateVertices(std::vector<Vertex>& vertices0, std::vector<Vertex> vertices1);
	static void ConcatenateIndices(std::vector<GLuint>& indices0, std::vector<GLuint> indices1);

	std::vector<glm::mat4> shape_transform;
protected:
	void AttachToGPU(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

	VertexArrayObject  m_VAO;
	VertexBufferObject m_VBO;
	IndexBufferObject  m_IBO;
	MatrixBufferObject m_MAT;

	GLuint m_IndicesCount = 0;
	GLuint m_InstanceCount = 0;
};