#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

class CylinderGeometryDetails
{
public:
	glm::vec3 TOP_ORIGO;
	GLfloat   TOP_RADIUS;
	glm::vec3 BOTTOM_ORIGO;
	GLfloat   BOTTOM_RADIUS;
	GLuint    COUNT;
};

class CylinderTextureDetails
{
public:
	GLfloat CIRCLE_ID;
	GLfloat WALL_ID;
};

class CylinderLayout
{
public:
	CylinderGeometryDetails GeometryDetails;
	CylinderTextureDetails  TextureDetails;

	static CylinderLayout GenerateBasicCylinderLayout();
};