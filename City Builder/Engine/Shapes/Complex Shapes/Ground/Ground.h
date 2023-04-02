#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class Ground : public Shape
{
public:
	Ground();
	void CreateBuffers() override;
};
