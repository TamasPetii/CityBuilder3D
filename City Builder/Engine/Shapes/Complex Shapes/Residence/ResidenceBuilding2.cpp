#include "ResidenceBuilding2.h"

ResidenceBuilding2::ResidenceBuilding2()
{
	GLfloat t = 0.45f;
	shape_transform.push_back(glm::translate(glm::vec3(t * -1, 0.15f, t * -1)) * glm::scale(glm::vec3(0.35f, 0.3f, 0.35f)));
	shape_transform.push_back(glm::translate(glm::vec3(t * 1, 0.15f, t * -1)) * glm::scale(glm::vec3(0.35f, 0.3f, 0.35f)));
	shape_transform.push_back(glm::translate(glm::vec3(t * -1, 0.15f, t * 1)) * glm::scale(glm::vec3(0.35f, 0.3f, 0.35f)));
	shape_transform.push_back(glm::translate(glm::vec3(t * 1, 0.15f, t * 1)) * glm::scale(glm::vec3(0.35f, 0.3f, 0.35f)));
}

void ResidenceBuilding2::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CylinderLayout cylinder_layout;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0, -0.5, 0);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.6f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0, 1.5, 0);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.6f;
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.TextureDetails.WALL_ID = 0.f;
	cylinder_layout.TextureDetails.CIRCLE_ID = 0.f;


	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));


	ConeLayout cone_layout;
	cone_layout.GeometryDetails.BASE_COUNT = 10;
	cone_layout.GeometryDetails.BASE_RADIUS = 0.9f;
	cone_layout.GeometryDetails.BASE_ORIGO = glm::vec3(0, 1.5, 0);
	cone_layout.GeometryDetails.BOTTOM_APEX = glm::vec3(0, 1.5, 0);
	cone_layout.GeometryDetails.TOP_APEX = glm::vec3(0, 2.5, 0);
	cone_layout.TextureDetails.ID = 1.f;

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(cone_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(cone_layout));

	AttachToGPU(vertices, indices);
}