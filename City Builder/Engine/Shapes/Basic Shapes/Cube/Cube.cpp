#include "Cube.h"

void Cube::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout layout = CubeLayout::GenerateBasicCubeLayout();
	
	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(layout));

	AttachToGPU(vertices, indices);
}

std::vector<Vertex> Cube::GenerateVertices(const CubeLayout& layout)
{
	std::vector<Vertex> vertices;

	//FRONT
	vertices.push_back({ layout.GeometryDetails.BOTTOM_FRONT_LEFT, glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.FRONT_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_FRONT_RIGHT,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.FRONT_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_FRONT_LEFT,glm::vec3(0),  glm::vec2(0, 1), layout.TextureDetails.FRONT_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_FRONT_RIGHT,glm::vec3(0),  glm::vec2(1, 1), layout.TextureDetails.FRONT_ID });

	//BACK
	vertices.push_back({ layout.GeometryDetails.BOTTOM_BACK_RIGHT,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.BACK_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_BACK_LEFT,glm::vec3(0),  glm::vec2(1, 0),layout.TextureDetails.BACK_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_BACK_RIGHT,glm::vec3(0),  glm::vec2(0, 1), layout.TextureDetails.BACK_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_BACK_LEFT,glm::vec3(0),  glm::vec2(1, 1), layout.TextureDetails.BACK_ID });

	//RIGHT
	vertices.push_back({ layout.GeometryDetails.BOTTOM_FRONT_RIGHT,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.RIGHT_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_BACK_RIGHT,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.RIGHT_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_FRONT_RIGHT,glm::vec3(0),  glm::vec2(0, 1), layout.TextureDetails.RIGHT_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_BACK_RIGHT,glm::vec3(0),  glm::vec2(1, 1), layout.TextureDetails.RIGHT_ID });

	//LEFT
	vertices.push_back({ layout.GeometryDetails.BOTTOM_BACK_LEFT,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.LEFT_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_FRONT_LEFT,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.LEFT_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_BACK_LEFT,glm::vec3(0),  glm::vec2(0, 1), layout.TextureDetails.LEFT_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_FRONT_LEFT,glm::vec3(0),  glm::vec2(1, 1), layout.TextureDetails.LEFT_ID });

	//TOP
	vertices.push_back({ layout.GeometryDetails.TOP_FRONT_LEFT,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.TOP_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_FRONT_RIGHT,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.TOP_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_BACK_LEFT,glm::vec3(0),  glm::vec2(0, 1), layout.TextureDetails.TOP_ID });
	vertices.push_back({ layout.GeometryDetails.TOP_BACK_RIGHT,glm::vec3(0),  glm::vec2(1, 1), layout.TextureDetails.TOP_ID });
	
	//BOTTOM
	vertices.push_back({ layout.GeometryDetails.BOTTOM_BACK_LEFT,glm::vec3(0),  glm::vec2(0, 0), layout.TextureDetails.BOTTOM_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_BACK_RIGHT,glm::vec3(0),  glm::vec2(1, 0), layout.TextureDetails.BOTTOM_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_FRONT_LEFT,glm::vec3(0),  glm::vec2(0, 1), layout.TextureDetails.BOTTOM_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_FRONT_RIGHT,glm::vec3(0),  glm::vec2(1, 1), layout.TextureDetails.BOTTOM_ID });

	return vertices;
}

std::vector<GLuint> Cube::GenerateIndices(const CubeLayout& layout, GLuint start)
{
	std::vector<GLuint> indices;

	for (int i = 0; i < 24; i += 4)
	{
		indices.push_back(start + i + 0);
		indices.push_back(start + i + 1);
		indices.push_back(start + i + 2);
		indices.push_back(start + i + 1);
		indices.push_back(start + i + 3);
		indices.push_back(start + i + 2);
	}

	return indices;
}