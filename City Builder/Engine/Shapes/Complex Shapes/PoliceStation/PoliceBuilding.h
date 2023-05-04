#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class PoliceBuilding : public Shape
{
public:
	PoliceBuilding();
	void CreateBuffers(GLuint buffer_size) override;
};
