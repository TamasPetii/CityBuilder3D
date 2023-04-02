#include "Pyramid.h"

void Pyramid::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	PyramidLayout layout = PyramidLayout::GenerateBasicPyramidLayout();

	Shape::ConcatenateIndices(indices, Pyramid::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Pyramid::GenerateVertices(layout));

	AttachToGPU(vertices, indices);
}

std::vector<Vertex> Pyramid::GenerateVertices(const const PyramidLayout& layout)
{
	std::vector<Vertex> vertices;

	vertices.push_back({ layout.GeometryDetails.TOP_APEX, glm::vec3(0),    glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Top Edge
	vertices.push_back({ layout.GeometryDetails.BOTTOM_APEX, glm::vec3(0), glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Bottom Edge

	//Diamond Side 1
	vertices.push_back({ layout.GeometryDetails.BASE_MM, glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_MP, glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.ID });
	//Diamond Side 2
	vertices.push_back({ layout.GeometryDetails.BASE_MP,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_PP,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.ID });
	//Diamond Side 3
	vertices.push_back({ layout.GeometryDetails.BASE_PP,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_PM,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.ID });
	//Diamond Side 4
	vertices.push_back({ layout.GeometryDetails.BASE_PM,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_MM,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.ID });

	return vertices;
}

std::vector<GLuint> Pyramid::GenerateIndices(const PyramidLayout& layout, GLuint start)
{
	std::vector<GLuint> indices;

	for (int i = 0; i < 8; i += 2)
	{
		//The first part of diamond (a pyramid)
		indices.push_back(start + 0);
		indices.push_back(start + 2 + i);
		indices.push_back(start + 2 + i + 1);

		//The second part of diamond (a reversed pyramid) (normaly only a rectangle)
		indices.push_back(start + 1);
		indices.push_back(start + 2 + i + 1);
		indices.push_back(start + 2 + i);
	}

	return indices;
}