#include "ResidenceBuilding1.h"

ResidenceBuilding1::ResidenceBuilding1()
{
	Transform transform;
	GLfloat t = 0.45f;

	for (int i = 0; i < 4; i++)
	{
		transform.translate = glm::translate(glm::vec3(t * (i % 2 ? 1 : -1), 0.175f, t * (i / 2 ? 1 : -1)));
		transform.rotate = glm::mat4(1);
		transform.scale = glm::scale(glm::vec3(0.35f));

		shape_transform.push_back(transform);
	}
}

void ResidenceBuilding1::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();
	cube_layout.TextureDetails.FRONT_ID = 16;
	cube_layout.TextureDetails.BACK_ID = 16;
	cube_layout.TextureDetails.LEFT_ID = 16;
	cube_layout.TextureDetails.RIGHT_ID = 16;
	cube_layout.TextureDetails.TOP_ID = 16;
	cube_layout.TextureDetails.BOTTOM_ID = 16;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	PyramidLayout pyramid_layout;
	pyramid_layout.GeometryDetails.BOTTOM_APEX = glm::vec3(0, cube_layout.GeometryDetails.TOP_BACK_LEFT.y, 0);
	pyramid_layout.GeometryDetails.TOP_APEX = glm::vec3(0, 1.f, 0);
	pyramid_layout.GeometryDetails.BASE_MM = cube_layout.GeometryDetails.TOP_BACK_LEFT + glm::vec3(-0.4, 0, -0.4);
	pyramid_layout.GeometryDetails.BASE_MP = cube_layout.GeometryDetails.TOP_FRONT_LEFT + glm::vec3(-0.4, 0, 0.4);
	pyramid_layout.GeometryDetails.BASE_PM = cube_layout.GeometryDetails.TOP_BACK_RIGHT + glm::vec3(0.4, 0, -0.4);
	pyramid_layout.GeometryDetails.BASE_PP = cube_layout.GeometryDetails.TOP_FRONT_RIGHT + glm::vec3(0.4, 0, 0.4);
	pyramid_layout.TextureDetails.ID = 24;

	Shape::ConcatenateIndices(indices, Pyramid::GenerateIndices(pyramid_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Pyramid::GenerateVertices(pyramid_layout));

	AttachToGPU(vertices, indices, buffer_size);
}