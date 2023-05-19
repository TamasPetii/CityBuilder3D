#include "Skybox.h"

void Skybox::CreateBuffers()
{
	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-1, -1, -1),
		glm::vec3(1, -1, -1),
		glm::vec3(1,  1, -1),
		glm::vec3(-1,  1, -1),
		glm::vec3(-1, -1,  1),
		glm::vec3(1, -1,  1),
		glm::vec3(1,  1,  1),
		glm::vec3(-1,  1,  1)
	};

	std::vector<GLuint> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 6, 5,
		6, 4, 7,
		0, 3, 4,
		4, 3, 7,
		1, 5, 2,
		5, 6, 2,
		1, 0, 4,
		1, 4, 5,
		3, 2, 6,
		3, 6, 7,
	};

	m_IndicesSize = static_cast<GLuint>(indices.size());

	m_VAO.Bind();
	m_VBO.AttachDataStatic(vertices);
	m_IBO.AttachDataStatic(indices);

	m_VAO.LinkAttribute(m_VBO, 0, 3, GL_FLOAT, sizeof(glm::vec3), nullptr);

	m_VAO.UnBind();
	m_VBO.UnBind();
	m_IBO.UnBind();
}

void Skybox::Render()
{
	GLint prevDepthFnc;
	glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFnc);
	glDepthFunc(GL_LEQUAL);

	m_VAO.Bind();
	glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, nullptr);
	m_VAO.UnBind();

	glDepthFunc(prevDepthFnc);
}