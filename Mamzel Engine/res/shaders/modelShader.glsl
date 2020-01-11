#VERTEX SHADER

#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;

out struct VertexOut
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoord;
} vOut;

uniform mat4 u_MatrixMVP;
uniform mat4 u_ObjectTransform;

void main()
{
    gl_Position = u_MatrixMVP * vec4(a_Position, 1.0);
    vOut.normal = normalize(mat3(transpose(inverse(u_ObjectTransform))) * a_Normal);
	vOut.fragPos = vec3(u_ObjectTransform * vec4(a_Position, 1.0));
	vOut.texCoord = a_TexCoord;
}

#FRAGMENT SHADER

#version 330 core


in struct VertexOut
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoord;
} vOut;

uniform struct Light
{
	vec3 position;

	float ambient;
	float diffuse;
	float specular;

	vec3 diffuseColor;
	vec3 specularColor;
} u_Light;

uniform vec3 u_CameraPos;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

out vec4 out_color;

float Diffuse(in vec3 lightDir, in vec3 normal)
{
	float diff = max(dot(normal, lightDir), 0.0);
	return diff;
}

float Blinn(in vec3 lightDir, in vec3 normal, in vec3 eye)
{
	vec3 halfwayDir = normalize(lightDir + eye);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
	return spec;
}

void main()
{    
	vec3 result = vec3(u_Light.ambient);
	
	vec3 norm = normalize(vOut.normal);
	vec3 viewDir = normalize(u_CameraPos - vOut.fragPos);
	vec3 lightDir = normalize(u_Light.position - vOut.fragPos);

	vec3 diffuse = Diffuse(lightDir, norm) * u_Light.diffuse * u_Light.diffuseColor;
	diffuse *= vec3(texture(texture_diffuse0, vOut.texCoord));

	vec3 specular = Blinn(lightDir, norm, viewDir) * u_Light.specular * u_Light.specularColor;
	specular *= vec3(texture(texture_specular0, vOut.texCoord));

	result += (diffuse + specular);

	out_color = vec4(1.0 - result, 1.0);
	//out_color = vec4(1.0);
}