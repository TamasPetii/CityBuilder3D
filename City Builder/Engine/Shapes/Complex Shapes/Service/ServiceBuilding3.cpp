#include "ServiceBuilding3.h"


ServiceBuilding3::ServiceBuilding3()
{
	Transform transform;
	GLfloat t = 0.45f;

	for (int i = 0; i < 4; i++)
	{
		transform.translate = glm::translate(glm::vec3(t * (i % 2 ? 1 : -1), 1, t * (i / 2 ? 1 : -1)));
		transform.rotate = glm::mat4(1);
		transform.scale = glm::mat4(1);

		shape_transform.push_back(transform);
	}
}

void ServiceBuilding3::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	
	ConeLayout cone_layout;
	cone_layout.GeometryDetails.BASE_COUNT = 10;
	cone_layout.GeometryDetails.BASE_RADIUS = 0.15f;
	cone_layout.GeometryDetails.BASE_ORIGO = glm::vec3(0, -1, 0);
	cone_layout.GeometryDetails.BOTTOM_APEX = glm::vec3(0, -1, 0);
	cone_layout.GeometryDetails.TOP_APEX = glm::vec3(0, 1, 0);
	cone_layout.TextureDetails.ID = 33.f;

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(cone_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(cone_layout));

	SphereLayout sphere_layout;
	sphere_layout.GeometryDetails.COUNT = 10;
	sphere_layout.GeometryDetails.RADIUS = 0.15f;
	sphere_layout.GeometryDetails.ORIGO = glm::vec3(0, 0.3, 0);
	sphere_layout.TextureDetails.ID = 34;

	Shape::ConcatenateIndices(indices, Sphere::GenerateIndices(sphere_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Sphere::GenerateVertices(sphere_layout));

	sphere_layout.GeometryDetails.RADIUS = 0.075f;
	sphere_layout.GeometryDetails.ORIGO = glm::vec3(0, 0.75, 0);

	Shape::ConcatenateIndices(indices, Sphere::GenerateIndices(sphere_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Sphere::GenerateVertices(sphere_layout));

	AttachToGPU(vertices, indices);
}