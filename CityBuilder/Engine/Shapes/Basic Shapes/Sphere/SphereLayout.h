#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

class SphereGeometryDetails
{
public:
	glm::vec3 ORIGO;
	GLfloat   RADIUS;
	GLuint   COUNT;
};

class SphereTextureDetails
{
public:
	GLfloat ID;
};

class SphereLayout
{
public:
	SphereGeometryDetails GeometryDetails;
	SphereTextureDetails  TextureDetails;

	static SphereLayout GenerateBasicSphereLayout();
};

