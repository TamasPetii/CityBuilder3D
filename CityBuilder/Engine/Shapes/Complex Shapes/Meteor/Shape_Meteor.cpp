#include "Shape_Meteor.h"

Shape_Meteor::Shape_Meteor()
{
	Transform transform;
	shape_transform.push_back(transform);
}

void Shape_Meteor::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	SphereLayout sphere_layout = SphereLayout::GenerateBasicSphereLayout();
	sphere_layout.TextureDetails.ID = 48;

	Shape::ConcatenateIndices(indices, Sphere::GenerateIndices(sphere_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Sphere::GenerateVertices(sphere_layout));

	AttachToGPU(vertices, indices, buffer_size);
}