#include "ResidenceBuilding3.h"

ResidenceBuilding3::ResidenceBuilding3()
{
	Transform transform;
	GLfloat t = 0.45f;

	for (int i = 0; i < 2; i++)
	{
		transform.translate = glm::translate(glm::vec3(0, 0.3f, 0.5f * (i % 2 ? 1 : -1)));
		transform.rotate = glm::mat4(1);
		transform.scale = glm::scale(glm::vec3(1.3f, 0.6f, 0.5f));

		shape_transform.push_back(transform);
	}
}

void ResidenceBuilding3::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();
	cube_layout.TextureDetails.FRONT_ID = 18;
	cube_layout.TextureDetails.BACK_ID = 18;
	cube_layout.TextureDetails.LEFT_ID = 18;
	cube_layout.TextureDetails.RIGHT_ID = 18;
	cube_layout.TextureDetails.TOP_ID = 28;
	cube_layout.TextureDetails.BOTTOM_ID = 28;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.6, 0.5, -0.6);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.6, 0.5, -0.6);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.6, 0.5, 0.6);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.6, 0.5, 0.6);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.4999, 1, 0);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.4999, 1, 0);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.4999, 1, 0);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.4999, 1, 0);

	cube_layout.TextureDetails.FRONT_ID = 27;
	cube_layout.TextureDetails.BACK_ID = 27;
	cube_layout.TextureDetails.LEFT_ID = 27;
	cube_layout.TextureDetails.RIGHT_ID = 27;
	cube_layout.TextureDetails.TOP_ID = 27;
	cube_layout.TextureDetails.BOTTOM_ID = 27;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices, buffer_size);
}