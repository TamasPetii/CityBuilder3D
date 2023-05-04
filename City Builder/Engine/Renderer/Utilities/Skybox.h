#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

#include "../../Abstractions/BufferObject.h"
#include "../../Abstractions/VertexArrayObject.h"
#include "../../Abstractions/Transform.h"

class Skybox
{
public:
	Skybox() {};
	~Skybox() {};

	void Render();
	void CreateBuffers();
private:
	VertexArrayObject     m_VAO;
	VectorBufferObject    m_VBO;
	IndexBufferObject     m_IBO;

	GLuint m_IndicesSize;
};

