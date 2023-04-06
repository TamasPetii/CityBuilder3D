#include "WindTurbinePropeller.h"


WindTurbinePropeller::WindTurbinePropeller()
{
	shape_transform.push_back(glm::translate(glm::vec3(0, 0.9, -0.2)) * glm::scale(glm::vec3(0.5, 0.5, 0.5)));
}

void WindTurbinePropeller::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-1, -0.1, -0.1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(1, -0.1, -0.1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-1, -0.1, 0.1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(1, -0.1, 0.1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-1, 0.1, -0.1);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(1, 0.1, -0.1);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-1, 0.1, 0.1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(1, 0.1, 0.1);

	cube_layout.TextureDetails.FRONT_ID = 70;
	cube_layout.TextureDetails.BACK_ID = 70;
	cube_layout.TextureDetails.LEFT_ID = 70;
	cube_layout.TextureDetails.RIGHT_ID = 70;
	cube_layout.TextureDetails.TOP_ID = 70;
	cube_layout.TextureDetails.BOTTOM_ID = 70;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.099, -1, -0.099);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.099, -1, -0.099);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.099, -1, 0.099);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.099, -1, 0.099);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.099, 1, -0.099);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.099, 1, -0.099);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.099, 1, 0.099);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.099, 1, 0.099);

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices);
}