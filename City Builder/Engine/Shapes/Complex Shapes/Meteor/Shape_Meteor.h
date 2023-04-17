#pragma once
#include "../../Basic Shapes/BasicShapes.h"

class Shape_Meteor : public Shape
{
public:
	Shape_Meteor();
	void CreateBuffers(GLuint buffer_size) override;
};