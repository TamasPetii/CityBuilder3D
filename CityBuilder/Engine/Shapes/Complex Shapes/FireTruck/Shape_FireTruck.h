#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class Shape_FireTruck : public Shape
{
public:
	Shape_FireTruck();
	void CreateBuffers(GLuint buffer_size) override;
};