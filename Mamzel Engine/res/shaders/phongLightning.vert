#version 440 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_MatrixMVP;
uniform mat4 u_ObjectTransform;

uniform float u_TextureRepeatCount;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_ObjectPos;

void main() 
{
	gl_Position = u_MatrixMVP * vec4(a_Pos, 1.0);
	v_TexCoord = a_TexCoord * u_TextureRepeatCount;
	v_Normal = mat3(transpose(inverse(u_ObjectTransform))) * a_Normal;
	v_ObjectPos = vec3(u_ObjectTransform * vec4(a_Pos, 1.0));
}