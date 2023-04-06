#include "ServiceBuilding1.h"


ServiceBuilding1::ServiceBuilding1()
{
	GLfloat t = 0.45f;
	shape_transform.push_back(glm::translate(glm::vec3(t * -1, 0.75, t * -1)) * glm::scale(glm::vec3(0.35, 1.5, 0.35)));
	shape_transform.push_back(glm::translate(glm::vec3(t * 1, 0.75, t * -1)) * glm::scale(glm::vec3(0.35, 1.5, 0.35)));
	shape_transform.push_back(glm::translate(glm::vec3(t * -1, 0.75, t * 1)) * glm::scale(glm::vec3(0.35, 1.5, 0.35)));
	shape_transform.push_back(glm::translate(glm::vec3(t * 1, 0.75, t * 1)) * glm::scale(glm::vec3(0.35, 1.5, 0.35)));
	
}

void ServiceBuilding1::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout = CubeLayout::GenerateBasicCubeLayout();
	cube_layout.TextureDetails.FRONT_ID = 13;
	cube_layout.TextureDetails.BACK_ID = 13;
	cube_layout.TextureDetails.LEFT_ID = 13;
	cube_layout.TextureDetails.RIGHT_ID = 13;
	cube_layout.TextureDetails.TOP_ID = 12;
	cube_layout.TextureDetails.BOTTOM_ID = 12;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices);
}