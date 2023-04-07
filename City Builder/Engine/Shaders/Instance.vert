#version 330 core

//Receiving Data
layout(location = 0) in vec3  vert_position;
layout(location = 1) in vec3  vert_normal;
layout(location = 2) in vec2  vert_texture;
layout(location = 3) in float vert_textureID;
layout(location = 4) in mat4 vert_translate;
layout(location = 8) in mat4 vert_rotate;
layout(location = 12) in mat4 vert_scale;

//Output Data
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
flat out int frag_textureID;

//Uniforms
uniform mat4 u_VP = mat4(1);
uniform mat4 u_M = mat4(1);

uniform mat4 u_translate;
uniform mat4 u_rotate;
uniform mat4 u_scale;

void main()
{
	//vec4 position = u_VP * u_translate * vert_translate * u_rotate * vert_rotate * u_scale * vert_scale * vec4(vert_position, 1);

	vec4 position = u_VP * vert_translate * vert_rotate  * vert_scale * u_translate * u_rotate * u_scale *  vec4(vert_position, 1);

	gl_Position = position;
	frag_position = position.xyz;
	frag_normal = vec3(0);
	frag_texture = vert_texture;
	frag_textureID = int(vert_textureID);
}