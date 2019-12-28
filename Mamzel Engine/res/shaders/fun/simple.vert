#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_Coord;

uniform mat4 u_MatrixMVP;

out vec2 v_Coord;

void main() 
{
	gl_Position = u_MatrixMVP * vec4(a_Pos, 1.0);
	v_Coord = a_Coord;
}
