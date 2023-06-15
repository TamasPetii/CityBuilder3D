#include "Shape_FireTruck.h"

Shape_FireTruck::Shape_FireTruck()
{
	Transform transform;
	transform.translate = glm::translate(glm::vec3(1, 0.5, 0));
	transform.rotate = glm::mat4(1);
	transform.scale = glm::mat4(10);

	shape_transform.push_back(transform);
}

void Shape_FireTruck::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	CubeLayout cube_layout;

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.5, 0.0, -0.14);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.5, 0.0, -0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.5, 0.0, 0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.5, 0.0, 0.14);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.5, 0.18, -0.14);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.5, 0.18, -0.14);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.5, 0.18, 0.14);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.5, 0.18, 0.14);

	cube_layout.TextureDetails.FRONT_ID = 55;
	cube_layout.TextureDetails.BACK_ID = 60;
	cube_layout.TextureDetails.LEFT_ID = 58;
	cube_layout.TextureDetails.RIGHT_ID = 57;
	cube_layout.TextureDetails.TOP_ID = 49;
	cube_layout.TextureDetails.BOTTOM_ID = 49;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(0.45, 0.18, 0);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.5, 0.18, 0);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(0.45, 0.18, 0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.5, 0.18, 0.14);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(0.45, 0.28, 0);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.47, 0.28, 0);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(0.45, 0.28, 0.14);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.47, 0.28, 0.14);

	cube_layout.TextureDetails.FRONT_ID = 56;
	cube_layout.TextureDetails.BACK_ID = 56;
	cube_layout.TextureDetails.LEFT_ID = 56;
	cube_layout.TextureDetails.RIGHT_ID = 56;
	cube_layout.TextureDetails.TOP_ID = 49;
	cube_layout.TextureDetails.BOTTOM_ID = 56;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(0.45, 0.18, -0.14);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.5, 0.18, -0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(0.45, 0.18, 0);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.5, 0.18, 0);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(0.45, 0.28, -0.14);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.47, 0.28, -0.14);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(0.45, 0.28, 0);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.47, 0.28, 0);

	cube_layout.TextureDetails.FRONT_ID = 56;
	cube_layout.TextureDetails.BACK_ID = 56;
	cube_layout.TextureDetails.LEFT_ID = 56;
	cube_layout.TextureDetails.RIGHT_ID = 56;
	cube_layout.TextureDetails.TOP_ID = 49;
	cube_layout.TextureDetails.BOTTOM_ID = 56;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(0.32, 0.18, -0.14);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.45, 0.18, -0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(0.32, 0.18, 0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.45, 0.18, 0.14);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(0.32, 0.28, -0.14);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.45, 0.28, -0.14);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(0.32, 0.28, 0.14);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.45, 0.28, 0.14);

	cube_layout.TextureDetails.FRONT_ID = 56;
	cube_layout.TextureDetails.BACK_ID = 56;
	cube_layout.TextureDetails.LEFT_ID = 56;
	cube_layout.TextureDetails.RIGHT_ID = 56;
	cube_layout.TextureDetails.TOP_ID = 49;
	cube_layout.TextureDetails.BOTTOM_ID = 56;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(0.15, 0.18, -0.14);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.32, 0.18, -0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(0.15, 0.18, 0.14);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.32, 0.18, 0.14);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(0.15, 0.28, -0.14);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.32, 0.28, -0.14);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(0.15, 0.28, 0.14);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.32, 0.28, 0.14);

	cube_layout.TextureDetails.FRONT_ID = 56;
	cube_layout.TextureDetails.BACK_ID = 56;
	cube_layout.TextureDetails.LEFT_ID = 56;
	cube_layout.TextureDetails.RIGHT_ID = 56;
	cube_layout.TextureDetails.TOP_ID = 49;
	cube_layout.TextureDetails.BOTTOM_ID = 56;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.5, 0.18, -0.1);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(-0.05, 0.18, -0.1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.5, 0.18, 0.1);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(-0.05, 0.18, 0.1);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.5, 0.28, -0.1);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(-0.05, 0.28, -0.1);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.5, 0.28, 0.1);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(-0.05, 0.28, 0.1);

	cube_layout.TextureDetails.FRONT_ID = 61;
	cube_layout.TextureDetails.BACK_ID = 61;
	cube_layout.TextureDetails.LEFT_ID = 61;
	cube_layout.TextureDetails.RIGHT_ID = 61;
	cube_layout.TextureDetails.TOP_ID = 49;
	cube_layout.TextureDetails.BOTTOM_ID = 61;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	cube_layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.4, 0.28, -0.04);
	cube_layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.7, 0.28, -0.04);
	cube_layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.4, 0.28, 0.04);
	cube_layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.7, 0.28, 0.04);

	cube_layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.4, 0.35, -0.04);
	cube_layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.7, 0.35, -0.04);
	cube_layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.4, 0.35, 0.04);
	cube_layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.7, 0.35, 0.04);

	cube_layout.TextureDetails.FRONT_ID = 59;
	cube_layout.TextureDetails.BACK_ID = 59;
	cube_layout.TextureDetails.LEFT_ID = 59;
	cube_layout.TextureDetails.RIGHT_ID = 59;
	cube_layout.TextureDetails.TOP_ID = 59;
	cube_layout.TextureDetails.BOTTOM_ID = 59;

	Shape::ConcatenateIndices(indices, Cube::GenerateIndices(cube_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cube::GenerateVertices(cube_layout));

	AttachToGPU(vertices, indices, buffer_size);
}