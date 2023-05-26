#include "SphereLayout.h"

SphereLayout SphereLayout::GenerateBasicSphereLayout()
{
	SphereLayout layout;
	layout.GeometryDetails.ORIGO = glm::vec3(0.f);
	layout.GeometryDetails.RADIUS = 0.5f;
	layout.GeometryDetails.COUNT = 15;
	layout.TextureDetails.ID = 0.f;

	return layout;
}