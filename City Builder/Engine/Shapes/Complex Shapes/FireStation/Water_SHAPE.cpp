#include "Water_SHAPE.h"

Water_SHAPE::Water_SHAPE()
{
	Transform transform;
	shape_transform.push_back(transform);
}

void Water_SHAPE::CreateBuffers(GLuint buffer_size)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	SphereLayout sphere_layout = SphereLayout::GenerateBasicSphereLayout();
	sphere_layout.GeometryDetails.RADIUS = 0.2;
	sphere_layout.TextureDetails.ID = 64;

	Shape::ConcatenateIndices(indices, Sphere::GenerateIndices(sphere_layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Sphere::GenerateVertices(sphere_layout));

	AttachToGPU(vertices, indices, buffer_size);
}