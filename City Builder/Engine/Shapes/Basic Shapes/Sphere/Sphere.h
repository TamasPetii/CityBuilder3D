#pragma once

#include "../../Shape.h"
#include "SphereLayout.h"


class Sphere : public Shape
{
public:
	void CreateBuffers(GLuint buffer_size) override;
	static std::vector<Vertex> GenerateVertices(const SphereLayout& layout);
	static std::vector<GLuint> GenerateIndices(const SphereLayout& layout, GLuint start);
private:
	static glm::vec3 GeneratePositions(const SphereLayout& layout, GLfloat u, GLfloat v);
	static glm::vec2 GenerateTextures(GLfloat u, GLfloat v);
};