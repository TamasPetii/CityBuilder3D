#include "FireBuilding.h"


FireBuilding::FireBuilding()
{
	Transform transform;
	transform.translate = glm::translate(glm::vec3(0, 0.5, 0));
	transform.rotate = glm::mat4(1);
	transform.scale = glm::mat4(1);

	shape_transform.push_back(transform);
}

void FireBuilding::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();
	cube_layout.TextureDetails.FRONT_ID = 50;
	cube_layout.TextureDetails.BACK_ID = 50;
	cube_layout.TextureDetails.LEFT_ID = 50;
	cube_layout.TextureDetails.RIGHT_ID = 50;
	cube_layout.TextureDetails.TOP_ID = 51;
	cube_layout.TextureDetails.BOTTOM_ID = 51;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices);
}