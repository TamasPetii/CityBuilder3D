#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

class PyramidGeometryDetails
{
public:
	glm::vec3 TOP_APEX;
	glm::vec3 BOTTOM_APEX;
	glm::vec3 BASE_MM; //MM -> Stands for X minus, Z minus: LEFT LEFT if you watching coordinate system from (0,0,1) point -> (-1, 0, -1)
	glm::vec3 BASE_PM; //PM -> Stands for X plus, Z minus: RIGHT LEFT if you watching coordinate system from (0,0,1) point -> ( 1, 0, -1)
	glm::vec3 BASE_PP; //PP -> Stands for X plus, Z plus: RIGHT RIGHT if you watching coordinate system from (0,0,1) point -> ( 1, 0,  1)
	glm::vec3 BASE_MP; //PM -> Stands for X minus, Z plus: RIGHT LEFT if you watching coordinate system from (0,0,1) point -> ( 1, 0, -1)
};

class PyramidTextureDetails
{
public:
	GLfloat ID;
};

class PyramidLayout
{
public:
	PyramidGeometryDetails GeometryDetails;
	PyramidTextureDetails  TextureDetails;

	static PyramidLayout GenerateBasicPyramidLayout();
};