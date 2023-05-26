#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class PowerBuildingPlinth : public Shape
{
public:
	PowerBuildingPlinth();
	void CreateBuffers(GLuint buffer_size) override;
};
