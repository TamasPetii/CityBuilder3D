#include "PowerWireBuilding.h"


PowerWireBuilding::PowerWireBuilding()
{
	Transform transform;
	transform.translate = glm::translate(glm::vec3(0, 0.5, 0));
	transform.rotate = glm::mat4(1);
	transform.scale = glm::scale(glm::vec3(1, 0.5, 1));

	shape_transform.push_back(transform);
}

void PowerWireBuilding::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CylinderLayout cylinder_layout;

	//Bottom cylinder
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0, 1, 0);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.1f;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0, -1, 0);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.1f;
	cylinder_layout.TextureDetails.CIRCLE_ID = 63;
	cylinder_layout.TextureDetails.WALL_ID = 63;

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));

	AttachToGPU(vertices, indices, buffer_size);
}

