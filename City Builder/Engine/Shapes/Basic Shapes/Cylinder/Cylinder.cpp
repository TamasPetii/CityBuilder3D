#include "Cylinder.h"

void Cylinder::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	
	CylinderLayout layout = CylinderLayout::GenerateBasicCylinderLayout();

	Shape::ConcatenateIndices(indices, Cylinder::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cylinder::GenerateVertices(layout));

	AttachToGPU(vertices, indices);
}

glm::vec3 Cylinder::GenerateVertexPositon(const glm::vec3 origo, GLfloat radius, GLfloat u)
{
	GLfloat theta = u * 2 * (float)M_PI;

	return origo + glm::vec3(radius * sin(theta), 0, radius * cos(theta));	
}

glm::vec2 Cylinder::GenerateTexturePosition(GLint part, GLfloat u)
{
	if (part == TOP_CIRCLE || part == BOTTOM_CIRCLE)
	{
		GLfloat theta = u * 2 * (float)M_PI;
		return glm::vec2((sin(theta) + 1.f) / 2.f, (cos(theta) + 1.f) / 2.f);
	}
	else if (part == TOP_WALL)
	{
		return glm::vec2(u, 1);
	}
	else
	{
		return glm::vec2(u, 0);
	}
}

std::vector<Vertex> Cylinder::GenerateVertices(const CylinderLayout& layout)
{
	std::vector<Vertex> vertices;

	vertices.push_back({ layout.GeometryDetails.TOP_ORIGO, glm::vec3(0), glm::vec2(0.5, 0.5), layout.TextureDetails.CIRCLE_ID });
	vertices.push_back({ layout.GeometryDetails.BOTTOM_ORIGO,glm::vec3(0), glm::vec2(0.5, 0.5), layout.TextureDetails.CIRCLE_ID });

	for (int i = 0; i < 4; ++i)
	{
		glm::vec3 origo  = (i == TOP_CIRCLE || i == TOP_WALL ? layout.GeometryDetails.TOP_ORIGO : layout.GeometryDetails.BOTTOM_ORIGO);
		GLfloat   radius = (i == TOP_CIRCLE || i == TOP_WALL ? layout.GeometryDetails.TOP_RADIUS : layout.GeometryDetails.BOTTOM_RADIUS);
		GLfloat   texID  = (i == TOP_CIRCLE || i == BOTTOM_CIRCLE ? layout.TextureDetails.CIRCLE_ID : layout.TextureDetails.WALL_ID);

		for (unsigned int j = 0; j <= layout.GeometryDetails.COUNT; j++)
		{
			GLfloat u = j / static_cast<float>(layout.GeometryDetails.COUNT);

			Vertex vert;
			vert.position = GenerateVertexPositon(origo, radius, u);
			vert.texture  = GenerateTexturePosition(i, u);
			vert.textureID = texID;

			if (i == TOP_CIRCLE)
				vert.normal = glm::vec3(0,1,0);
			else if (i == BOTTOM_CIRCLE)
				vert.normal = glm::vec3(0, -1, 0);
			else
				vert.normal = glm::normalize(GenerateVertexPositon(origo, radius, u) - origo);

			vertices.push_back(vert);
		}
	}

	return vertices;
}

std::vector<GLuint> Cylinder::GenerateIndices(const CylinderLayout& layout, GLuint start)
{
	std::vector<GLuint> indices;

	for (unsigned int i = 0; i < layout.GeometryDetails.COUNT; i++)
	{
		indices.push_back(start);
		indices.push_back(start + 2 + i);
		indices.push_back(start + 2 + (i + 1));
		indices.push_back(start + 1);
		indices.push_back(start + 2 + (layout.GeometryDetails.COUNT + 1)  + (i + 1));
		indices.push_back(start + 2 + (layout.GeometryDetails.COUNT + 1)  + i);
	}
	
	start += 2 + 2 * (layout.GeometryDetails.COUNT + 1);
	
	for (unsigned int i = 0; i <= layout.GeometryDetails.COUNT; i++)
	{
		indices.push_back(start + i);
		indices.push_back(start + layout.GeometryDetails.COUNT + i);
		indices.push_back(start + layout.GeometryDetails.COUNT + (i + 1));

		indices.push_back(start + i);
		indices.push_back(start + layout.GeometryDetails.COUNT + (i + 1));
		indices.push_back(start + i + 1);
	}
	
	return indices;
}