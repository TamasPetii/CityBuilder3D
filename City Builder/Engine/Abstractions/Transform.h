#pragma once

#include <GLM/glm.hpp>

struct Transform
{
	glm::mat4 translate = glm::mat4(1);
	glm::mat4 rotate = glm::mat4(1);
	glm::mat4 scale = glm::mat4(1);

	static glm::mat4 MultiplyTransformMatrices(Transform transform) { return transform.translate * transform.rotate * transform.scale; }
};

