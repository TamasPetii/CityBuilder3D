#include "Pyramid.h"

void Pyramid::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	PyramidLayout layout = PyramidLayout::GenerateBasicPyramidLayout();

	Shape::ConcatenateIndices(indices, Pyramid::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Pyramid::GenerateVertices(layout));

	AttachToGPU(vertices, indices);
}

std::vector<Vertex> Pyramid::GenerateVertices(const PyramidLayout& layout)
{
	std::vector<Vertex> vertices;
	glm::vec3 normal;

	//Diamond Upper Side 1
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_MM, layout.GeometryDetails.BASE_MP);
	vertices.push_back({ layout.GeometryDetails.TOP_APEX, normal,    glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Top vertex
	vertices.push_back({ layout.GeometryDetails.BASE_MM, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_MP, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });
	//Diamond Upper Side 2
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_MP, layout.GeometryDetails.BASE_PP);
	vertices.push_back({ layout.GeometryDetails.TOP_APEX, normal,    glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Top vertex
	vertices.push_back({ layout.GeometryDetails.BASE_MP, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_PP, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });
	//Diamond Upper Side 3
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_PP, layout.GeometryDetails.BASE_PM);
	vertices.push_back({ layout.GeometryDetails.TOP_APEX, normal,    glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Top vertex
	vertices.push_back({ layout.GeometryDetails.BASE_PP, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_PM, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });
	//Diamond Upper Side 4
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_PM, layout.GeometryDetails.BASE_MM);
	vertices.push_back({ layout.GeometryDetails.TOP_APEX, normal,    glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Top vertex
	vertices.push_back({ layout.GeometryDetails.BASE_PM, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_MM, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });

	//Diamond Lower Side 1
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_MP, layout.GeometryDetails.BASE_MM);
	vertices.push_back({ layout.GeometryDetails.BOTTOM_APEX, normal, glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Bottom vertex
	vertices.push_back({ layout.GeometryDetails.BASE_MP, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_MM, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });
	//Diamond Lower Side 2
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_PP, layout.GeometryDetails.BASE_MP);
	vertices.push_back({ layout.GeometryDetails.BOTTOM_APEX, glm::vec3(0), glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Bottom vertex
	vertices.push_back({ layout.GeometryDetails.BASE_PP, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_MP, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });
	//Diamond Lower Side 3
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_PM, layout.GeometryDetails.BASE_PP);
	vertices.push_back({ layout.GeometryDetails.BOTTOM_APEX, glm::vec3(0), glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Bottom vertex
	vertices.push_back({ layout.GeometryDetails.BASE_PM, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_PP, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });
	//Diamond Lower Side 4
	normal = Shape::GenerateNormal(layout.GeometryDetails.TOP_APEX, layout.GeometryDetails.BASE_MM, layout.GeometryDetails.BASE_PM);
	vertices.push_back({ layout.GeometryDetails.BOTTOM_APEX, glm::vec3(0), glm::vec2(0.5, 1), layout.TextureDetails.ID }); // Bottom vertex
	vertices.push_back({ layout.GeometryDetails.BASE_MM, normal,  glm::vec2(1, 0), layout.TextureDetails.ID });
	vertices.push_back({ layout.GeometryDetails.BASE_PM, normal,  glm::vec2(0, 0), layout.TextureDetails.ID });

	return vertices;
}

std::vector<GLuint> Pyramid::GenerateIndices(const PyramidLayout& layout, GLuint start)
{
	std::vector<GLuint> indices;

	for (int i = 0; i <= 21; i += 3)
	{
		//Both the upper part (a pyramid) and the lower part of the diamond (a reversed pyramid) (normaly only a rectangle) is generated here
		indices.push_back(start + i);
		indices.push_back(start + 1 + i);
		indices.push_back(start + 2 + i);
	}

	return indices;
}