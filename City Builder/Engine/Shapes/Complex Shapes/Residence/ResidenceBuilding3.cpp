#include "ResidenceBuilding3.h"

ResidenceBuilding3::ResidenceBuilding3()
{
	shape_transform.push_back(glm::translate(glm::vec3(0.f, 0.6f, -0.5f)) * glm::scale(glm::vec3(1.3f, 1.2f, 0.5f)));
	shape_transform.push_back(glm::translate(glm::vec3(0.f, 0.6f, 0.5f)) * glm::scale(glm::vec3(1.3f, 1.2f, 0.5f)));
}

void ResidenceBuilding3::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();
	cube_layout.TextureDetails.FRONT_ID = 31;
	cube_layout.TextureDetails.BACK_ID = 31;
	cube_layout.TextureDetails.LEFT_ID = 31;
	cube_layout.TextureDetails.RIGHT_ID = 31;
	cube_layout.TextureDetails.TOP_ID = 32;
	cube_layout.TextureDetails.BOTTOM_ID = 32;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices);
}