#pragma once

#include "../../Basic Shapes/BasicShapes.h"

class IndustryBuilding1 : public Shape
{
public:
	IndustryBuilding1();
	void CreateBuffers(GLuint buffer_size) override;
};