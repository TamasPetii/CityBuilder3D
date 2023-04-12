#include "IndustryBuilding1.h"

IndustryBuilding1::IndustryBuilding1()
{
	Transform transform;
	transform.translate = glm::translate(glm::vec3(0.f, 0.3f, -0.5f));
	transform.rotate = glm::mat4(1);
	transform.scale = glm::mat4(1);

	shape_transform.push_back(transform);
}

void IndustryBuilding1::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout;

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.5, -0.3, 0.5);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.5, -0.3, 0.5);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.5, -0.3, 1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.5, -0.3, 1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.5, 0.3, 0.5);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.5, 0.3, 0.5);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.5, 0.3, 1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.5, 0.3, 1);

	cube_layout.TextureDetails.BACK_ID = 30;
	cube_layout.TextureDetails.FRONT_ID = 30;
	cube_layout.TextureDetails.RIGHT_ID = 30;
	cube_layout.TextureDetails.LEFT_ID = 30;
	cube_layout.TextureDetails.TOP_ID = 36;
	cube_layout.TextureDetails.BOTTOM_ID = 36;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	CylinderLayout cylinder_layout;
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(-0.25, -0.25, 0.25);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.15f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(-0.25, 1, 0.25);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;
	cylinder_layout.TextureDetails.WALL_ID = 33;
	cylinder_layout.TextureDetails.CIRCLE_ID = 33;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0.25, -0.3, 0.25);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.15f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0.25, 1, 0.25);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	AttachToGPU(vertices, indices);
}