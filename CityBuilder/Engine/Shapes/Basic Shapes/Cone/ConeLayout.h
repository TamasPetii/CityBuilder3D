#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

class ConeGeometryDetails
{
public:
	glm::vec3 TOP_APEX;
	glm::vec3 BOTTOM_APEX;
	glm::vec3 BASE_ORIGO;
	GLfloat   BASE_RADIUS;
	GLuint    BASE_COUNT;
};

class ConeTextureDetails
{
public:
	GLfloat ID;
};

class ConeLayout 
{
public:
	ConeGeometryDetails GeometryDetails;
	ConeTextureDetails  TextureDetails;

	static ConeLayout GenerateBasicConeLayout();
};
