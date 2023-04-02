#include "PowerWireBuilding.h"


PowerWireBuilding::PowerWireBuilding()
{
	shape_transform.push_back(glm::translate(glm::vec3(0, 0, 0)) * glm::scale(glm::vec3(1, 0.0001, 1)));
}

void PowerWireBuilding::CreateBuffers()
{
	//TODO: Some pillar + wire
}