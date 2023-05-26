#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class WindTurbinePropeller : public Shape
{
public:
	WindTurbinePropeller();
	void CreateBuffers(GLuint buffer_size) override;
};
