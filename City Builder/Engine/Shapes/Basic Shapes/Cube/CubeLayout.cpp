#include "CubeLayout.h"

CubeLayout CubeLayout::GenerateBasicCubeLayout()
{
	CubeLayout layout;
	layout.GeometryDetails.BOTTOM_BACK_LEFT = glm::vec3(-0.5, -0.5, -0.5);
	layout.GeometryDetails.BOTTOM_BACK_RIGHT = glm::vec3(0.5, -0.5, -0.5);
	layout.GeometryDetails.BOTTOM_FRONT_LEFT = glm::vec3(-0.5, -0.5, 0.5);
	layout.GeometryDetails.BOTTOM_FRONT_RIGHT = glm::vec3(0.5, -0.5, 0.5);

	layout.GeometryDetails.TOP_BACK_LEFT = glm::vec3(-0.5, 0.5, -0.5);
	layout.GeometryDetails.TOP_BACK_RIGHT = glm::vec3(0.5, 0.5, -0.5);
	layout.GeometryDetails.TOP_FRONT_LEFT = glm::vec3(-0.5, 0.5, 0.5);
	layout.GeometryDetails.TOP_FRONT_RIGHT = glm::vec3(0.5, 0.5, 0.5);

	layout.TextureDetails.BACK_ID = 0.f;
	layout.TextureDetails.FRONT_ID = 0.f;
	layout.TextureDetails.RIGHT_ID = 0.f;
	layout.TextureDetails.LEFT_ID = 0.f;
	layout.TextureDetails.TOP_ID = 1.f;
	layout.TextureDetails.BOTTOM_ID = 1.f;

	return layout;
}