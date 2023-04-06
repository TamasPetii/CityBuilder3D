#include "ServiceBuilding2.h"


ServiceBuilding2::ServiceBuilding2()
{
	GLfloat t = 0.45f;
	shape_transform.push_back(glm::translate(glm::vec3(t * -1, 0.3, t * -1)) * glm::scale(glm::vec3(0.4, 0.6, 0.4)));
	shape_transform.push_back(glm::translate(glm::vec3(t * 1, 0.3, t * -1)) * glm::scale(glm::vec3(0.4, 0.6, 0.4)));
	shape_transform.push_back(glm::translate(glm::vec3(t * -1, 0.3, t * 1)) * glm::scale(glm::vec3(0.4, 0.6, 0.4)));
	shape_transform.push_back(glm::translate(glm::vec3(t * 1, 0.3, t * 1)) * glm::scale(glm::vec3(0.4, 0.6, 0.4)));

}

void ServiceBuilding2::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout;

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.45, -0.5, -0.45);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.45, -0.5, -0.45);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.45, -0.5, 0.45);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.45, -0.5, 0.45);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.4, 0.5, -0.4);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.4, 0.5, -0.4);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.4, 0.5, 0.4);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.4, 0.5, 0.4);

	cube_layout.TextureDetails.BACK_ID = 23;
	cube_layout.TextureDetails.FRONT_ID = 23;
	cube_layout.TextureDetails.RIGHT_ID = 23;
	cube_layout.TextureDetails.LEFT_ID = 23;
	cube_layout.TextureDetails.TOP_ID = 22;
	cube_layout.TextureDetails.BOTTOM_ID = 22;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.3, 0.5, -0.3);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.3, 0.5, -0.3);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.3, 0.5, 0.3);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.3, 0.5, 0.3);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.25, 1.5, -0.25);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.25, 1.5, -0.25);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.25, 1.5, 0.25);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.25, 1.5, 0.25);

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.15, 1.5, -0.15);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.15, 1.5, -0.15);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.15, 1.5, 0.15);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.15, 1.5, 0.15);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.125, 2.5, -0.125);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.125, 2.5, -0.125);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.125, 2.5, 0.125);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.125, 2.5, 0.125);

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices);
}