#include "IndustryBuilding3.h"

IndustryBuilding3::IndustryBuilding3()
{
	shape_transform.push_back(glm::translate(glm::vec3(0.f, 0.3f, 0.2f)) * glm::scale(glm::vec3(1)));
}

void IndustryBuilding3::CreateBuffers()
{

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout;

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.5, -0.3, -0.5);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.5, -0.3, -0.5);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.5, -0.3, 0);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.5, -0.3, 0);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.5, 0.3, -0.5);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.5, 0.3, -0.5);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.5, 0.3, 0);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.5, 0.3, 0);

	cube_layout.TextureDetails.BACK_ID = 97;
	cube_layout.TextureDetails.FRONT_ID = 97;
	cube_layout.TextureDetails.RIGHT_ID = 97;
	cube_layout.TextureDetails.LEFT_ID = 97;
	cube_layout.TextureDetails.TOP_ID = 94;
	cube_layout.TextureDetails.BOTTOM_ID = 94;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.4, 0.3, -0.4);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.4, 0.3, -0.4);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.4, 0.3,-0.1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.4, 0.3, -0.1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.4, 0.6, -0.4);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.4, 0.6, -0.4);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.4, 0.6, -0.1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.4, 0.6, -0.1);

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	CylinderLayout cylinder_layout;
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(-0.3, -0.3, -0.7);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.15f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(-0.3, 1, -0.7);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;
	cylinder_layout.TextureDetails.WALL_ID = 98;
	cylinder_layout.TextureDetails.CIRCLE_ID = 98;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));


	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0.3, -0.3, -0.7);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.15f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0.3, 1, -0.7);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	//-------------------------------------------------------

	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(-0.3, -0.3, 0.2);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.15f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(-0.3, 1, 0.2);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0.3, -0.3, 0.2);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.15f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0.3, 1, 0.2);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	AttachToGPU(vertices, indices);

}