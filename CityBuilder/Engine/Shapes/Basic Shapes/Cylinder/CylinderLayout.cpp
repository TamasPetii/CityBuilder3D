#include "CylinderLayout.h"

CylinderLayout CylinderLayout::GenerateBasicCylinderLayout()
{
	CylinderLayout layout;
	layout.GeometryDetails.TOP_ORIGO = glm::vec3(0, 0.5, 0);
	layout.GeometryDetails.TOP_RADIUS = 0.5;
	layout.GeometryDetails.BOTTOM_ORIGO = glm::vec3(0, -0.5, 0);
	layout.GeometryDetails.BOTTOM_RADIUS = 0.5;
	layout.GeometryDetails.COUNT = 10;
	layout.TextureDetails.CIRCLE_ID = 0.f;
	layout.TextureDetails.WALL_ID = 1.f;

	return layout;
}