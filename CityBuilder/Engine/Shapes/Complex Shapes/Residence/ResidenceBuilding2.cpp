#include "ResidenceBuilding2.h"

ResidenceBuilding2::ResidenceBuilding2()
{
	Transform transform;
	GLfloat t = 0.45f;

	for (int i = 0; i < 4; i++)
	{
		transform.translate = glm::translate(glm::vec3(t * (i % 2 ? 1 : -1), 0.15f, t * (i / 2 ? 1 : -1)));
		transform.rotate = glm::mat4(1);
		transform.scale = glm::scale(glm::vec3(0.35f, 0.3f, 0.35f));

		shape_transform.push_back(transform);
	}
}

void ResidenceBuilding2::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CylinderLayout cylinder_layout;
	cylinder_layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0, -0.5, 0);
	cylinder_layout.GeometryDetails.BOTTOM_RADIUS = 0.6f;
	cylinder_layout.GeometryDetails.TOP_ORIGO = glm::vec3(0, 1.5, 0);
	cylinder_layout.GeometryDetails.TOP_RADIUS = 0.6f;
	cylinder_layout.GeometryDetails.COUNT = 10;
	cylinder_layout.TextureDetails.WALL_ID = 21;
	cylinder_layout.TextureDetails.CIRCLE_ID = 21;


	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(cylinder_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(cylinder_layout));


	ConeLayout cone_layout;
	cone_layout.GeometryDetails.BASE_COUNT = 10;
	cone_layout.GeometryDetails.BASE_RADIUS = 0.9f;
	cone_layout.GeometryDetails.BASE_ORIGO = glm::vec3(0, 1.5, 0);
	cone_layout.GeometryDetails.BOTTOM_APEX = glm::vec3(0, 1.5, 0);
	cone_layout.GeometryDetails.TOP_APEX = glm::vec3(0, 2.5, 0);
	cone_layout.TextureDetails.ID = 14;

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(cone_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(cone_layout));

	AttachToGPU(vertices, indices, buffer_size);
}