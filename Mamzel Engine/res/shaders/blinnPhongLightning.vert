#version 440 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

struct VertexOut
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoord;
};

uniform mat4 u_MatrixMVP;
uniform mat4 u_ObjectTransform;

uniform float u_TextureScale;

out VertexOut vOut;

void main() 
{
	gl_Position = u_MatrixMVP * vec4(a_Pos, 1.0);

	vOut.normal = mat3(transpose(inverse(u_ObjectTransform))) * a_Normal;
	vOut.fragPos = vec3(u_ObjectTransform * vec4(a_Pos, 1.0));
	vOut.texCoord = a_TexCoord * u_TextureScale;
}