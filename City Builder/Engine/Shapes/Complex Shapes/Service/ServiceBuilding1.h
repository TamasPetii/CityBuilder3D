#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class ServiceBuilding1 : public Shape
{
public:
	ServiceBuilding1();
	void CreateBuffers(GLuint buffer_size) override;
};
