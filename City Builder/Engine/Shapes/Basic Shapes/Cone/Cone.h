#pragma once
#include "../../Shape.h"
#include "ConeLayout.h"

class Cone : public Shape
{
public:
	void CreateBuffers() override;
	static std::vector<Vertex> GenerateVertices(const ConeLayout& layout);
	static std::vector<GLuint> GenerateIndices(const ConeLayout& layout, GLuint start);
};