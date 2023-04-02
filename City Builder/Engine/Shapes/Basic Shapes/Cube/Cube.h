#pragma once

#include "../../Shape.h"
#include "CubeLayout.h"

class Cube : public Shape
{
public:
	void CreateBuffers() override;
	static std::vector<Vertex> GenerateVertices(const CubeLayout& layout);
	static std::vector<GLuint> GenerateIndices(const CubeLayout& layout, GLuint start);
};