#include "Shape_Car.h"

Shape_Car::Shape_Car()
{
	Transform transform;
	transform.translate = glm::translate(glm::vec3(1, 0.5, 0));
	transform.rotate = glm::mat4(1);
	transform.scale = glm::mat4(10);

	shape_transform.push_back(transform);
}

void Shape_Car::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout;

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.25, 0.0, -0.115);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.3, 0.0, -0.115);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.25, 0.0, 0.115);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.3, 0.0, 0.115);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.25, 0.14, -0.115);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.3, 0.14, -0.115);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.25, 0.14, 0.115);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.3, 0.14, 0.115);

	cube_layout.TextureDetails.FRONT_ID = 53;
	cube_layout.TextureDetails.BACK_ID = 53;
	cube_layout.TextureDetails.LEFT_ID = 54;
	cube_layout.TextureDetails.RIGHT_ID = 52;
	cube_layout.TextureDetails.TOP_ID = 51;
	cube_layout.TextureDetails.BOTTOM_ID = 51;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.01, 0.14, -0.115);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.16, 0.14, -0.115);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.01, 0.14, 0.115);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.16, 0.14, 0.115);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.01, 0.21, -0.095);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.1, 0.21, -0.095);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.01, 0.21, 0.095);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.1, 0.21, 0.095);

	cube_layout.TextureDetails.FRONT_ID = 50;
	cube_layout.TextureDetails.BACK_ID = 50;
	cube_layout.TextureDetails.LEFT_ID = 50;
	cube_layout.TextureDetails.RIGHT_ID = 50;
	cube_layout.TextureDetails.TOP_ID = 51;
	cube_layout.TextureDetails.BOTTOM_ID = 51;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.16, 0.14, -0.115);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(-0.01, 0.14, -0.115);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.16, 0.14, 0.115);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(-0.01, 0.14, 0.115);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.1, 0.21, -0.095);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(-0.01, 0.21, -0.095);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.1, 0.21, 0.095);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(-0.01, 0.21, 0.095);

	cube_layout.TextureDetails.FRONT_ID = 50;
	cube_layout.TextureDetails.BACK_ID = 50;
	cube_layout.TextureDetails.LEFT_ID = 50;
	cube_layout.TextureDetails.RIGHT_ID = 50;
	cube_layout.TextureDetails.TOP_ID = 51;
	cube_layout.TextureDetails.BOTTOM_ID = 51;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices, buffer_size);
}