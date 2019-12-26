#version 440 core

layout(location = 0) in vec3 a_Pos;

uniform mat4 u_MatrixMVP;

void main() 
{
	gl_Position = u_MatrixMVP * vec4(a_Pos, 1.0);
}