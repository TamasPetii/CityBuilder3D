#version 330 core

vec3[2] x;

uniform vec3 u_RayStart;
uniform vec3 u_RayEnd;
uniform mat4 u_MVP;

void main()
{
	vec3 rays[2] = vec3[2](u_RayStart,u_RayEnd);
	gl_Position = u_MVP * vec4(rays[gl_VertexID], 1);
}