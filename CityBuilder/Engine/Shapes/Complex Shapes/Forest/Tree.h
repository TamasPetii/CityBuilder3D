#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class Tree : public Shape 
{
public:
	Tree();
	void CreateBuffers(GLuint buffer_size) override;
};