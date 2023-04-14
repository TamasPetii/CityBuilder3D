#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

#include "../Abstractions/BufferObject.h"
#include "../Abstractions/VertexArrayObject.h"
#include "../Abstractions/Transform.h"

class Shape
{
public:
	static void ConcatenateVertices(std::vector<Vertex>& vertices0, std::vector<Vertex> vertices1);
	static void ConcatenateIndices(std::vector<GLuint>& indices0, std::vector<GLuint> indices1);

	virtual void CreateBuffers(GLuint buffer_size) = 0;

	void Bind() const;
	void UnBind() const;
	void Render() const;
	void RenderInstanced() const;

	void AttachMatricesDynamic(const std::vector<glm::mat4>& transforms);
	void AttachMatricesSubData(const std::vector<glm::mat4>& transforms);

	void AttachNumbersDynamic(const std::vector<GLfloat>& numbers);
	void AttachNumbersSubData(const std::vector<GLfloat>& numbers);

	static glm::vec3 GenerateNormal(glm::vec3 start, glm::vec3 destination1, glm::vec3 destination2);

	inline GLuint Get_IndicesCount() const { return m_IndicesCount; }
	inline GLuint Get_InstanceCount() const { return m_InstanceCount; }
	inline std::vector<Transform> Get_Transforms() { return shape_transform; }
protected:
	void AttachToGPU(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint buffer_size);

	VertexArrayObject     m_VAO;
	VertexBufferObject    m_VBO;
	IndexBufferObject     m_IBO;
	MatrixBufferObject    m_MBO;
	NumberBufferObject    m_NBO;

	GLuint m_IndicesCount = 0;
	GLuint m_InstanceCount = 0;

	std::vector<Transform> shape_transform;
};