#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class StadionBuilding : public Shape
{
public:
	StadionBuilding();
	void CreateBuffers(GLuint buffer_size) override;
};
