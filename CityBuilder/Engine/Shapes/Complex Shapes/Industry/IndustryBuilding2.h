#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class IndustryBuilding2 : public Shape
{
public:
	IndustryBuilding2();
	void CreateBuffers(GLuint buffer_size) override;
};