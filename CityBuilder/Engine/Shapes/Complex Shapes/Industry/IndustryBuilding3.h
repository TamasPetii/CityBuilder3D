#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class IndustryBuilding3 : public Shape
{
public:
	IndustryBuilding3();
	void CreateBuffers(GLuint buffer_size) override;
};