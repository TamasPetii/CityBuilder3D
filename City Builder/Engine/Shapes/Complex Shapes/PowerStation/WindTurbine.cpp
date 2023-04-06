#include "WindTurbine.h"


WindTurbine::WindTurbine()
{
	shape_transform.push_back(glm::translate(glm::vec3(0, 0.6, 0)) * glm::scale(glm::vec3(1, 0.6, 1)));
}

void WindTurbine::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CylinderLayout cylinder_layout;

	//Bottom cylinder
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0, 1, 0);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0, -1, 0);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.15f;
	cylinder_layout.TextureDetails.CIRCLE_ID = 50;
	cylinder_layout.TextureDetails.WALL_ID = 50;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	AttachToGPU(vertices, indices);
}