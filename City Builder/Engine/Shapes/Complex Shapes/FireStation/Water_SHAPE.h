#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class Water_SHAPE : public Shape
{
public:
	Water_SHAPE();
	void CreateBuffers(GLuint buffer_size) override;
};
