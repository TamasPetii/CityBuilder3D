#version 330 core

//Receiving Data
layout(location = 0) in vec3  vert_position;
layout(location = 1) in vec3  vert_normal;
layout(location = 2) in vec2  vert_texture;
layout(location = 3) in float vert_textureID;
layout(location = 4) in mat4  vert_matrix;

//Output Data
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
flat out int frag_textureID;

//Uniforms
uniform mat4 u_VP = mat4(1);
uniform mat4 u_M = mat4(1);

void main(){
	gl_Position = u_VP * vert_matrix * u_M  * vec4(vert_position, 1);

	frag_position = (vert_matrix * u_M * vec4(vert_position, 1)).xyz;
	frag_normal = vec3(0);
	frag_texture = vert_texture;
	frag_textureID = int(vert_textureID);
}