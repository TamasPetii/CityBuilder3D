#include "Cone.h"

void Cone::CreateBuffers()
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	ConeLayout layout = ConeLayout::GenerateBasicConeLayout();

	Shape::ConcatenateIndices(indices, Cone::GenerateIndices(layout, (GLuint)vertices.size()));
	Shape::ConcatenateVertices(vertices, Cone::GenerateVertices(layout));

	AttachToGPU(vertices, indices);
}

std::vector<Vertex> Cone::GenerateVertices(const ConeLayout& layout)
{
	Vertex vert;
	std::vector<Vertex> vertices;

	//Apex of the cone at top
	vert.position = layout.GeometryDetails.TOP_APEX;
	vert.texture = glm::vec2(0.5, 1);
	vert.textureID = layout.TextureDetails.ID;
	vert.normal = glm::vec3(0, 1, 0);
	vertices.push_back(vert);

	//Apex of the cone at bottom (In case we want to render a shape looks like 2 cone on each other)
	//In a normal case this is the same as BASE_ORIGO
	vert.position = layout.GeometryDetails.BOTTOM_APEX;
	vert.texture = glm::vec2(0.5, 1);
	vert.textureID = layout.TextureDetails.ID;
	vert.normal = glm::vec3(0, -1, 0);
	vertices.push_back(vert);

	for (unsigned int i = 0; i <= layout.GeometryDetails.BASE_COUNT; i++)
	{
		float u = i / float(layout.GeometryDetails.BASE_COUNT);

		//Cross production of the vector from the base circle's current point to the apex with a vector on the xy plane in the current angle gives us the normal vector
		float angle = -(u * 2 * M_PI);
		glm::vec3 pos_on_circle = glm::vec3(layout.GeometryDetails.BASE_RADIUS * sin(u * 2 * M_PI), layout.GeometryDetails.BASE_ORIGO.y, layout.GeometryDetails.BASE_RADIUS * cos(u * 2 * M_PI));
		glm::vec3 vector_in_angle = glm::normalize(glm::vec3(cos(angle),0,sin(angle)));
		glm::vec3 pos_to_apex = glm::normalize(layout.GeometryDetails.TOP_APEX - pos_on_circle);
		glm::vec3 upper_normal = glm::normalize(glm::cross(vector_in_angle, pos_to_apex));

		//Calculating the normal for the lower part
		pos_to_apex = glm::normalize(layout.GeometryDetails.BOTTOM_APEX - pos_on_circle);
		glm::vec3 lower_normal = glm::normalize(glm::cross(pos_to_apex, vector_in_angle));

		//We will go around of a circle and calculate points locatied on the arc of circle. (We use the circle's paramteric formula!)
		vert.position = glm::vec3(layout.GeometryDetails.BASE_RADIUS * sin(u * 2 * M_PI), layout.GeometryDetails.BASE_ORIGO.y, layout.GeometryDetails.BASE_RADIUS * cos(u * 2 * M_PI));
		vert.texture = glm::vec2(u, 0);
		vert.textureID = layout.TextureDetails.ID;
		vert.normal = upper_normal;
		vertices.push_back(vert);

		//Lower circle
		vert.position = glm::vec3(layout.GeometryDetails.BASE_RADIUS * sin(u * 2 * M_PI), layout.GeometryDetails.BASE_ORIGO.y, layout.GeometryDetails.BASE_RADIUS * cos(u * 2 * M_PI));
		vert.texture = glm::vec2(u, 0);
		vert.textureID = layout.TextureDetails.ID;
		vert.normal = lower_normal;
		vertices.push_back(vert);
	}

	return vertices;
}

std::vector<GLuint> Cone::GenerateIndices(const ConeLayout& layout, GLuint start)
{
	std::vector<GLuint> indices;

	for (unsigned int i = 0; i < (layout.GeometryDetails.BASE_COUNT * 2); i+=2)
	{
		//Connecting the apex with two circle points (We will get the wall)
		indices.push_back(start);
		indices.push_back(start + 2 + i);
		indices.push_back(start + 4 + i);

		//Connecting the origo with two circle points (We will get the bottom circle)
		indices.push_back(start + 1);
		indices.push_back(start + 5 + i);
		indices.push_back(start + 3 + i);
	}

	return indices;
}