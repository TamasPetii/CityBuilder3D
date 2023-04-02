#include "PyramidLayout.h"

PyramidLayout PyramidLayout::GenerateBasicPyramidLayout()
{
	PyramidLayout layout;
	layout.GeometryDetails.TOP_APEX = glm::vec3(0.f, 0.5f, 0.f);
	layout.GeometryDetails.BOTTOM_APEX = glm::vec3(0.f, -0.5f, 0.f);
	layout.GeometryDetails.BASE_MM = glm::vec3(-0.5f, -0.5f, -0.5f);
	layout.GeometryDetails.BASE_PM = glm::vec3(0.5f, -0.5f, -0.5f);
	layout.GeometryDetails.BASE_PP = glm::vec3(0.5f, -0.5f, 0.5f);
	layout.GeometryDetails.BASE_MP = glm::vec3(-0.5f, -0.5f, 0.5f);
	layout.TextureDetails.ID = 0.f;

	return layout;
}