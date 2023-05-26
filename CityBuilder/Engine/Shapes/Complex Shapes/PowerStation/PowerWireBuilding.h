#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class PowerWireBuilding : public Shape
{
public:
	PowerWireBuilding();
	void CreateBuffers(GLuint buffer_size) override;
};
