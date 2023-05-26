#include "ServiceBuilding1.h"


ServiceBuilding1::ServiceBuilding1()
{
	Transform transform;
	GLfloat t = 0.45f;

	for (int i = 0; i < 4; i++)
	{
		transform.translate = glm::translate(glm::vec3(t * (i % 2 ? 1 : -1), 0.75, t * (i / 2 ? 1 : -1)));
		transform.rotate = glm::mat4(1);
		transform.scale = glm::scale(glm::vec3(0.35, 1.5, 0.35));

		shape_transform.push_back(transform);
	}
	
}

void ServiceBuilding1::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();
	cube_layout.TextureDetails.FRONT_ID = 20;
	cube_layout.TextureDetails.BACK_ID = 20;
	cube_layout.TextureDetails.LEFT_ID = 20;
	cube_layout.TextureDetails.RIGHT_ID = 20;
	cube_layout.TextureDetails.TOP_ID = 24;
	cube_layout.TextureDetails.BOTTOM_ID = 24;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices, buffer_size);
}