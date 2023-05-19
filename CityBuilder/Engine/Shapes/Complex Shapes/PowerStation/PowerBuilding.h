#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class PowerBuilding : public Shape
{
public:
	PowerBuilding();
	void CreateBuffers(GLuint buffer_size) override;
};
