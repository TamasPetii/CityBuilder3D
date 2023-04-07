#include "Ground.h"

Ground::Ground()
{
	Transform transform;
	transform.scale = glm::scale(glm::vec3(2, 0.001, 2));

	shape_transform.push_back(transform);
}

void Ground::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices);
}