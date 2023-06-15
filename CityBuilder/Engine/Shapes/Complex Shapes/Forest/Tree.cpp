#include "Tree.h"

Tree::Tree() 
{
	Transform transform;
	GLfloat t = 0.6f;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			transform.translate = glm::translate(glm::vec3(t * i, 0.3f, t * j));
			transform.rotate = glm::mat4(1);
			transform.scale = glm::scale(glm::vec3(0.15f, 0.3f, 0.15f));

			shape_transform.push_back(transform);
		}
	}
}

void Tree::CreateBuffers(GLuint buffer_size)
{
	
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	ConeLayout layout;
	layout.GeometryDetails.BASE_COUNT = 10;
	layout.GeometryDetails.BASE_RADIUS = 1.f;
	layout.GeometryDetails.BASE_ORIGO = glm::vec3(0, 1, 0);
	layout.GeometryDetails.BOTTOM_APEX = glm::vec3(0, 1, 0);
	layout.GeometryDetails.TOP_APEX = glm::vec3(0, 2, 0);
	layout.TextureDetails.ID = 35.f;

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(layout));

	layout.GeometryDetails.BASE_ORIGO += glm::vec3(0, -0.5, 0);
	layout.GeometryDetails.BOTTOM_APEX += glm::vec3(0, -0.5, 0);
	layout.GeometryDetails.TOP_APEX += glm::vec3(0, -0.5, 0);

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(layout));

	layout.GeometryDetails.BASE_ORIGO += glm::vec3(0, -0.5, 0);
	layout.GeometryDetails.BOTTOM_APEX += glm::vec3(0, -0.5, 0);
	layout.GeometryDetails.TOP_APEX += glm::vec3(0, -0.5, 0);

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(layout));

	//This will be the trunk
	layout.GeometryDetails.BASE_ORIGO += glm::vec3(0, -1, 0);
	layout.GeometryDetails.BOTTOM_APEX += glm::vec3(0, -1, 0);
	layout.GeometryDetails.TOP_APEX = glm::vec3(0, 2, 0);
	layout.GeometryDetails.BASE_RADIUS = 0.2f;
	layout.TextureDetails.ID = 34.f;

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(layout));

	AttachToGPU(vertices, indices, buffer_size);
}