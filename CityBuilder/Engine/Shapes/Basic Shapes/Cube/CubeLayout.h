#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

class CubeGeometryDetails
{
public:
	glm::vec3 BOTTOM_BACK_LEFT;
	glm::vec3 BOTTOM_BACK_RIGHT;
	glm::vec3 BOTTOM_FRONT_LEFT;
	glm::vec3 BOTTOM_FRONT_RIGHT;

	glm::vec3 TOP_BACK_LEFT;
	glm::vec3 TOP_BACK_RIGHT;
	glm::vec3 TOP_FRONT_LEFT;
	glm::vec3 TOP_FRONT_RIGHT;
};

class CubeTextureDetails
{
public:
	GLfloat TOP_ID;
	GLfloat BOTTOM_ID;
	GLfloat LEFT_ID;
	GLfloat RIGHT_ID;
	GLfloat BACK_ID;
	GLfloat FRONT_ID;
};

class CubeLayout
{
public:
	CubeGeometryDetails GeometryDetails;
	CubeTextureDetails  TextureDetails;

	static CubeLayout GenerateBasicCubeLayout();
};
