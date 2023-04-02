#pragma once

#include "Vertex.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "ProgramObject.h"

#include <vector>
#include <string>

struct Tex 
{
	GLuint id;
	std::string type;
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Tex>& textures);

	std::vector<Tex> textures;

	void Render(ProgramObject* program, const glm::mat4& transform);
	void RenderInstanced(ProgramObject* program, const std::vector<glm::mat4>& transforms);
	VertexArrayObject m_VAO;
	VertexBufferObject m_VBO;
	IndexBufferObject m_IBO;
	MatrixBufferObject m_MBO;

	GLuint m_IndicesCount = 0;
	GLuint m_InstanceCount = 0;
private:
	void AttachToGPU(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

};

