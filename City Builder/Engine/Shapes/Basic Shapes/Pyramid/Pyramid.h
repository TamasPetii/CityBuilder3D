#pragma once

#include "../../Shape.h"
#include "PyramidLayout.h"

class Pyramid : public Shape
{
public:
	void CreateBuffers() override;
	static std::vector<Vertex> GenerateVertices(const PyramidLayout& layout);
	static std::vector<GLuint> GenerateIndices(const PyramidLayout&, GLuint start);
};