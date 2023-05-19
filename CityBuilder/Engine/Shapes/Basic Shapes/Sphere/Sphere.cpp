#include "Sphere.h"

void Sphere::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	SphereLayout layout = SphereLayout::GenerateBasicSphereLayout();

	Shape::ConcatenateIndices(indices, Sphere::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Sphere::GenerateVertices(layout));

	AttachToGPU(vertices, indices, buffer_size);
}

std::vector<Vertex> Sphere::GenerateVertices(const SphereLayout& layout)
{
	std::vector<Vertex> vertices((layout.GeometryDetails.COUNT + 1) * (layout.GeometryDetails.COUNT + 1));

	for (unsigned int i = 0; i <= layout.GeometryDetails.COUNT; i++)
	{
		for (unsigned int j = 0; j <= layout.GeometryDetails.COUNT; j++)
		{
			GLfloat u = i / (GLfloat)layout.GeometryDetails.COUNT;
			GLfloat v = j / (GLfloat)layout.GeometryDetails.COUNT;
			glm::vec3 normal = glm::normalize(GeneratePositions(layout, u, v) - layout.GeometryDetails.ORIGO);
			vertices[i + j * (layout.GeometryDetails.COUNT + 1)] = { GeneratePositions(layout, u, v), normal, GenerateTextures(u, v) , layout.TextureDetails.ID };
		}
	}

	return vertices;
}

std::vector<GLuint> Sphere::GenerateIndices(const SphereLayout& layout, GLuint start)
{
	std::vector<GLuint> indices(6 * layout.GeometryDetails.COUNT * layout.GeometryDetails.COUNT);

	for (unsigned int i = 0; i < layout.GeometryDetails.COUNT; ++i)
	{
		for (unsigned int j = 0; j < layout.GeometryDetails.COUNT; ++j)
		{
			indices[6 * i + j * 3 * 2 * (layout.GeometryDetails.COUNT)+0] = start + (i)+(j) * (layout.GeometryDetails.COUNT + 1);
			indices[6 * i + j * 3 * 2 * (layout.GeometryDetails.COUNT)+1] = start + (i + 1) + (j) * (layout.GeometryDetails.COUNT + 1);
			indices[6 * i + j * 3 * 2 * (layout.GeometryDetails.COUNT)+2] = start + (i)+(j + 1) * (layout.GeometryDetails.COUNT + 1);
			indices[6 * i + j * 3 * 2 * (layout.GeometryDetails.COUNT)+3] = start + (i + 1) + (j) * (layout.GeometryDetails.COUNT + 1);
			indices[6 * i + j * 3 * 2 * (layout.GeometryDetails.COUNT)+4] = start + (i + 1) + (j + 1) * (layout.GeometryDetails.COUNT + 1);
			indices[6 * i + j * 3 * 2 * (layout.GeometryDetails.COUNT)+5] = start + (i)+(j + 1) * (layout.GeometryDetails.COUNT + 1);
		}
	}

	return indices;
}

glm::vec3 Sphere::GeneratePositions(const SphereLayout& layout, GLfloat u, GLfloat v)
{
	u *= 2 * (float)M_PI;
	v *= (float)M_PI;

	glm::vec3 position =
	{
		layout.GeometryDetails.RADIUS * sin(v) * cos(u),
		layout.GeometryDetails.RADIUS * cos(v),
		layout.GeometryDetails.RADIUS * sin(v) * sin(u)
	};

	return layout.GeometryDetails.ORIGO + position;
}
glm::vec2 Sphere::GenerateTextures(GLfloat u, GLfloat v)
{
	return glm::vec2(1 - u, 1 - v);
}