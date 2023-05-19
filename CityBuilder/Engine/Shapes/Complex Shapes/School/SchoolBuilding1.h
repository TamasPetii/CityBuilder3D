#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class SchoolBuilding1 : public Shape
{
public:
	SchoolBuilding1();
	void CreateBuffers(GLuint buffer_size) override;
};

