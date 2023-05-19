#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class WindTurbine : public Shape
{
public:
	WindTurbine();
	void CreateBuffers(GLuint buffer_size) override;
};
