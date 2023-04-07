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
	static glm::mat4 MultiplyTransformMatrices(Transform transform) { return transform.translate * transform.rotate * transform.scale; }

	virtual void CreateBuffers() = 0;

	void Bind() const;
	void UnBind() const;
	void Render() const;
	void RenderInstanced() const;

	void AttachTransformsDynamic(const std::vector<Transform>& transforms);
	void AttachTransformsSubData(const std::vector<Transform>& transforms);

	// <<GETTER>> //
	inline std::vector<Transform> Get_Transforms() { return shape_transform; }
	inline GLuint Get_IndicesCount() const { return m_IndicesCount; }
	inline GLuint Get_InstanceCount() const { return m_InstanceCount; }
protected:
	void AttachToGPU(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

	VertexArrayObject     m_VAO;
	VertexBufferObject    m_VBO;
	IndexBufferObject     m_IBO;
	TransformBufferObject m_TBO;

	GLuint m_IndicesCount = 0;
	GLuint m_InstanceCount = 0;

	std::vector<Transform> shape_transform;
};