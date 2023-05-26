#include "ConeLayout.h"

ConeLayout ConeLayout::GenerateBasicConeLayout()
{
	ConeLayout layout;
	layout.GeometryDetails.TOP_APEX = glm::vec3(0.f, 0.5f, 0.f);
	layout.GeometryDetails.BOTTOM_APEX = glm::vec3(0.f, -0.5f, 0.f);
	layout.GeometryDetails.BASE_ORIGO = glm::vec3(0.f, -0.5f, 0.f);
	layout.GeometryDetails.BASE_RADIUS = 1.f;
	layout.GeometryDetails.BASE_COUNT = 10;
	layout.TextureDetails.ID = 0.f;

	return layout;
}