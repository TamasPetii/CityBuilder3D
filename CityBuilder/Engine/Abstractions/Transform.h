#pragma once

#include <GLM/glm.hpp>

/**
 * A struct representing a transformation in 3D space.
 * Contains matrices for translation, rotation, and scaling.
 */
struct Transform
{
	glm::mat4 translate = glm::mat4(1);
	glm::mat4 rotate = glm::mat4(1);
	glm::mat4 scale = glm::mat4(1);

	static glm::mat4 ConvertToMatrix(Transform transform) { return transform.translate * transform.rotate * transform.scale; }
};

