#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class Shape_Car : public Shape
{
public:
	Shape_Car();
	void CreateBuffers(GLuint buffer_size) override;
};