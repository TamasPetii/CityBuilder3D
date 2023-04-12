#include "StadionBuilding.h"


StadionBuilding::StadionBuilding()
{
	Transform transform;
	transform.translate = glm::translate(glm::vec3(0, 0.2, 0));
	transform.rotate = glm::mat4(1);
	transform.scale = glm::scale(glm::vec3(0.3, 0.2, 0.3));

	shape_transform.push_back(transform);
}

void StadionBuilding::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout;

	//Football Field
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-1, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(1, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-1, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(1, -1, 1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-1, -0.99, -1);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(1, -0.99, -1);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-1, -0.99, 1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(1, -0.99, 1);

	cube_layout.TextureDetails.BACK_ID = 45;
	cube_layout.TextureDetails.FRONT_ID = 45;
	cube_layout.TextureDetails.RIGHT_ID = 45;
	cube_layout.TextureDetails.LEFT_ID = 45;
	cube_layout.TextureDetails.TOP_ID = 45;
	cube_layout.TextureDetails.BOTTOM_ID = 45;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Left Triangle Wall
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-2, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(-1, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-2, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(-1, -1, 1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-2, 1, -1);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(-2, 1, -1);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-2, 1, 1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(-2, 1, 1);

	cube_layout.TextureDetails.BACK_ID = 43;
	cube_layout.TextureDetails.FRONT_ID = 43;
	cube_layout.TextureDetails.RIGHT_ID = 44;
	cube_layout.TextureDetails.LEFT_ID = 43;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Right Triangle Wall
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(1, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(2, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(1, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(2, -1, 1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(2, 1, -1);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(2, 1, -1);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(2, 1, 1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(2, 1, 1);

	cube_layout.TextureDetails.BACK_ID = 43;
	cube_layout.TextureDetails.FRONT_ID = 43;
	cube_layout.TextureDetails.RIGHT_ID = 43;
	cube_layout.TextureDetails.LEFT_ID = 44;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Back Triangle Wall
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-1, -1, -2);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(1, -1, -2);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-1, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(1, -1, -1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-1, 1, -2);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(1, 1, -2);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-1, 1, -2);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(1, 1, -2);

	cube_layout.TextureDetails.BACK_ID = 43;
	cube_layout.TextureDetails.FRONT_ID = 44;
	cube_layout.TextureDetails.RIGHT_ID = 43;
	cube_layout.TextureDetails.LEFT_ID = 43;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Front Triangle Wall
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-1, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(1, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-1, -1, 2);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(1, -1, 2);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-1, 1, 2);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(1, 1, 2);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-1, 1, 2);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(1, 1, 2);

	cube_layout.TextureDetails.BACK_ID = 44;
	cube_layout.TextureDetails.FRONT_ID = 43;
	cube_layout.TextureDetails.RIGHT_ID = 43;
	cube_layout.TextureDetails.LEFT_ID = 43;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Left Back Edge
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-2, -1, -2);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(-1, -1, -2);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-2, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(-1, -1, -1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-2, 1, -2);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(-1, 1, -2);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-2, 1, -1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(-1, 1, -2); //This vertex creates edge effect

	cube_layout.TextureDetails.BACK_ID = 43;
	cube_layout.TextureDetails.FRONT_ID = 44;
	cube_layout.TextureDetails.RIGHT_ID = 43;
	cube_layout.TextureDetails.LEFT_ID = 43;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Rigth Back Edge

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(1, -1, -2);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(2, -1, -2);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(1, -1, -1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(2, -1, -1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(1, 1, -2);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(2, 1, -2);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(1.999, 1, -1); //This vertex creates edge effect
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(2, 1, -1);

	cube_layout.TextureDetails.BACK_ID = 43;
	cube_layout.TextureDetails.FRONT_ID = 43;
	cube_layout.TextureDetails.RIGHT_ID = 43;
	cube_layout.TextureDetails.LEFT_ID = 44;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Left Back Edge
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-2, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(-1, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-2, -1, 2);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(-1, -1, 2);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-2, 1, 1);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(-2, 1, 1);//This vertex creates edge effect
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-2, 1, 2);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(-1, 1, 2);

	cube_layout.TextureDetails.BACK_ID = 43;
	cube_layout.TextureDetails.FRONT_ID = 43;
	cube_layout.TextureDetails.RIGHT_ID = 44;
	cube_layout.TextureDetails.LEFT_ID = 43;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	//Left Back Edge
	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(1, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(2, -1, 1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(1, -1, 2);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(2, -1, 2);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(1, 1, 1.999);//This vertex creates edge effect
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(2, 1, 1);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(1, 1, 2);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(2, 1, 2);

	cube_layout.TextureDetails.BACK_ID = 44;
	cube_layout.TextureDetails.FRONT_ID = 43;
	cube_layout.TextureDetails.RIGHT_ID = 43;
	cube_layout.TextureDetails.LEFT_ID = 43;
	cube_layout.TextureDetails.TOP_ID = 43;
	cube_layout.TextureDetails.BOTTOM_ID = 43;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices);
}