#VERTEX SHADER

#version 440 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

out struct VertexOut
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoord;
} vOut;

uniform mat4 u_MatrixMVP;
uniform mat4 u_ObjectTransform;

uniform float u_TextureScale;

void main() 
{
	gl_Position = u_MatrixMVP * vec4(a_Pos, 1.0);
	vOut.normal = mat3(transpose(inverse(u_ObjectTransform))) * a_Normal;
	vOut.fragPos = vec3(u_ObjectTransform * vec4(a_Pos, 1.0));
	vOut.texCoord = a_TexCoord * u_TextureScale;
}

#FRAGMENT SHADER

# version 440 core

in struct VertexOut
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoord;
} vOut;

uniform struct Light
{
	float ambient;
	float diffuse;
	float specular;

	// count of point light sources in the scene
	int count;
	
	// max count is 32
	vec3 positions[32];

	// attunement multipliers
	float constant[32];
	float linear[32];
	float quadratic[32];

	vec3 diffuseColor[32];
	vec3 specularColor[32];
} u_Light;

uniform struct GlobalLight
{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specularColor;
	float intensity;
} u_GlobalLight;

uniform vec3 u_ObjectColor;
uniform vec3 u_CameraPos;

uniform int u_UseBlinn;
uniform int u_UseGlobalLight;

uniform int u_UseTexture;
uniform sampler2D u_TextureSampler;

out vec4 out_color;

float Diffuse(in vec3 lightDir, in vec3 normal)
{
	float diff = max(dot(normal, lightDir), 0.0);
	return diff;
}

float Phong(in vec3 lightDir, in vec3 normal, in vec3 eye)
{
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, eye), 0.0), 32);
	return spec;
}

float Blinn(in vec3 lightDir, in vec3 normal, in vec3 eye)
{
	vec3 halfwayDir = normalize(lightDir + eye);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
	return spec;
}

void main()
{
	// One ambient component
	vec3 result = vec3(u_Light.ambient);
	
	vec3 norm = normalize(vOut.normal);
	vec3 viewDir = normalize(u_CameraPos - vOut.fragPos);

	vec3 diffuse, specular;

	// Point lights
	for (int i = 0; i < u_Light.count; i++)
	{	
		float distFormLight = length(u_Light.positions[i] - vOut.fragPos);
		float attenuation = 1.0 / ((u_Light.constant[i]) + (u_Light.linear[i] * distFormLight) + (u_Light.quadratic[i] * distFormLight * distFormLight));

		vec3 lightDir = normalize(u_Light.positions[i] - vOut.fragPos);
		
		diffuse =  Diffuse(lightDir, norm) * u_Light.diffuse * u_Light.diffuseColor[i] * attenuation;
		
		if (u_UseBlinn == 0)
			specular = Phong(lightDir, norm, viewDir) * u_Light.specular * u_Light.specularColor[i] * attenuation;
		else
			specular = Blinn(lightDir, norm, viewDir) * u_Light.specular * u_Light.specularColor[i] * attenuation;

		result += (diffuse + specular);
	}

	// Global light
	if (u_UseGlobalLight == 1)
	{
		diffuse = Diffuse(-u_GlobalLight.direction, norm) * u_GlobalLight.intensity * u_GlobalLight.diffuseColor;

		if (u_UseBlinn == 0)
			specular = Phong(-u_GlobalLight.direction, norm, viewDir) * u_GlobalLight.intensity * u_GlobalLight.specularColor;
		else
			specular = Blinn(-u_GlobalLight.direction, norm, viewDir) * u_GlobalLight.intensity * u_GlobalLight.specularColor;

		result += (diffuse + specular);
	}
	
	result *= u_ObjectColor;

	if (u_UseTexture == 0)
		out_color = vec4(result, 1.0);
	else
		out_color = texture(u_TextureSampler, vOut.texCoord) * vec4(result, 1.0);
}