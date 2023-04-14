#pragma once

#include "../../Shape.h"
#include "CylinderLayout.h"

class Cylinder : public Shape
{
public:
	void CreateBuffers(GLuint buffer_size) override;
	static std::vector<Vertex> GenerateVertices(const CylinderLayout& layout);
	static std::vector<GLuint> GenerateIndices(const CylinderLayout& layout, GLuint start);
private:
	static glm::vec3 GenerateVertexPositon(const glm::vec3 origo, GLfloat radius, GLfloat u);
	static glm::vec2 GenerateTexturePosition(GLint part, GLfloat u);
	enum CylinderParts {TOP_CIRCLE, BOTTOM_CIRCLE, TOP_WALL, BOTTOM_WALL};
};