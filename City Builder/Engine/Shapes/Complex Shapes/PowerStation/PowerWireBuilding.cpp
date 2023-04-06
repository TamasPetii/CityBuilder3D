#include "PowerWireBuilding.h"


PowerWireBuilding::PowerWireBuilding()
{
	shape_transform.push_back(glm::translate(glm::vec3(0, 0.5, 0)) * glm::scale(glm::vec3(1, 0.5, 1)));
}

void PowerWireBuilding::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CylinderLayout cylinder_layout;

	//Bottom cylinder
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0, 1, 0);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.1f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0, -1, 0);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;
	cylinder_layout.TextureDetails.CIRCLE_ID = 99;
	cylinder_layout.TextureDetails.WALL_ID = 99;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	AttachToGPU(vertices, indices);
}

