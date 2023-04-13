#include "WindTurbinePropeller.h"


WindTurbinePropeller::WindTurbinePropeller()
{
	Transform transform;
	transform.translate = glm::translate(glm::vec3(0, 1.25, -0.15));
	transform.rotate = glm::mat4(1);
	transform.scale = glm::scale(glm::vec3(0.65, 0.65, 0.65));

	shape_transform.push_back(transform);
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

	cube_layout.TextureDetails.FRONT_ID = 61;
	cube_layout.TextureDetails.BACK_ID = 61;
	cube_layout.TextureDetails.LEFT_ID = 61;
	cube_layout.TextureDetails.RIGHT_ID = 61;
	cube_layout.TextureDetails.TOP_ID = 61;
	cube_layout.TextureDetails.BOTTOM_ID = 61;

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