#include "PowerBuildingPlinth.h"


PowerBuildingPlinth::PowerBuildingPlinth()
{
	shape_transform.push_back(glm::translate(glm::vec3(0, 1.3, 0)) * glm::scale(glm::vec3(0.5, 1, 0.5)));
}

void PowerBuildingPlinth::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CylinderLayout cylinder_layout;

	//Bottom cylinder
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0, -1.3, 0);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 1.1f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0, -1, 0);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 1.f;
	cylinder_layout.TextureDetails.CIRCLE_ID = 0.f;
	cylinder_layout.TextureDetails.WALL_ID = 1.f;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	AttachToGPU(vertices, indices);
}