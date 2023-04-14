#version 330 core

//Receiving Data
layout(location = 0) in vec3  vert_position;
layout(location = 1) in vec3  vert_normal;
layout(location = 2) in vec2  vert_texture;
layout(location = 3) in float vert_textureID;
layout(location = 4) in float vert_id;
layout(location = 5) in mat4  vert_transforms;

//Output Data
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
flat out int frag_textureID;

//Uniforms
uniform float u_UseVertexTexID = 0;
uniform mat4 u_VP = mat4(1);
uniform mat4 u_M = mat4(1);

void main()
{
	vec4 position = vert_transforms * u_M *  vec4(vert_position, 1);
	vec4 normal = inverse(transpose(vert_transforms * u_M)) * vec4(vert_normal, 1);

	gl_Position = u_VP * position;
	frag_position = position.xyz;
	frag_normal = normal.xyz;
	frag_texture = vert_texture;
	frag_textureID = (int(u_UseVertexTexID) == 0 ? int(vert_textureID) : int(vert_id));
}