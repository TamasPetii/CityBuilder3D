#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class FireBuilding : public Shape
{
public:
	FireBuilding();
	void CreateBuffers(GLuint buffer_size) override;
};
