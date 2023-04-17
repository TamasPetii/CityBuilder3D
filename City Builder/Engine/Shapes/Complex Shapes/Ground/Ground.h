#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class Ground : public Shape
{
public:
	Ground();
	void CreateBuffers(GLuint buffer_size) override;
};
