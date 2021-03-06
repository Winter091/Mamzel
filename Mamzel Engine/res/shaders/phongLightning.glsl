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

uniform float u_TextureScale = 1.0;

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

uniform struct PointLight
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
} u_PointLight;

uniform struct DirectionalLight
{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specularColor;
	float intensity;
} u_DirectionalLight;

uniform vec4 u_ObjectColor;
uniform vec3 u_CameraPos;

uniform bool u_UseBlinn;
uniform bool u_UseDirectionalLight = false;

uniform bool u_UseDiffuseTexture = false;
uniform bool u_UseSpecularTexture = false;
uniform sampler2D u_DiffuseTextureSampler;
uniform sampler2D u_SpecularTextureSampler;

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
	vec3 norm = normalize(vOut.normal);
	vec3 viewDir = normalize(u_CameraPos - vOut.fragPos);

	vec4 totalDiffuse = vec4(vec3(0.0), 1.0), totalSpecular = vec4(vec3(0.0), 1.0);
	vec4 diffuse, specular;

	totalDiffuse += vec4(vec3(u_PointLight.ambient), 0.0);

	// Point lights
	for (int i = 0; i < u_PointLight.count; i++)
	{	
		float distFormLight = length(u_PointLight.positions[i] - vOut.fragPos);
		float attenuation = 1.0 / ((u_PointLight.constant[i]) + (u_PointLight.linear[i] * distFormLight) + (u_PointLight.quadratic[i] * distFormLight * distFormLight));

		vec3 lightDir = normalize(u_PointLight.positions[i] - vOut.fragPos);

		diffuse =  vec4(Diffuse(lightDir, norm) * u_PointLight.diffuse * u_PointLight.diffuseColor[i] * attenuation, 0.0);

		if (u_UseBlinn)
			specular = vec4(Blinn(lightDir, norm, viewDir) * u_PointLight.specular * u_PointLight.specularColor[i] * attenuation, 0.0);
		else
			specular = vec4(Phong(lightDir, norm, viewDir) * u_PointLight.specular * u_PointLight.specularColor[i] * attenuation, 0.0);

		totalDiffuse += diffuse;
		totalSpecular += specular;
	}

	// Directional light
	if (u_UseDirectionalLight)
	{
		vec3 lightDirection = normalize(u_DirectionalLight.direction);

		diffuse = vec4(Diffuse(-lightDirection, norm) * u_DirectionalLight.intensity * u_DirectionalLight.diffuseColor, 0.0);

		if (u_UseBlinn)
			specular = vec4(Blinn(-lightDirection, norm, viewDir) * u_DirectionalLight.intensity * u_DirectionalLight.specularColor, 0.0);
		else
			specular = vec4(Phong(-lightDirection, norm, viewDir) * u_DirectionalLight.intensity * u_DirectionalLight.specularColor, 0.0);

		totalDiffuse += diffuse;
		totalSpecular += specular;
	}
	
	if (u_UseDiffuseTexture)
		totalDiffuse *= texture(u_DiffuseTextureSampler, vOut.texCoord);

	if (u_UseSpecularTexture)
		totalSpecular *= texture(u_SpecularTextureSampler, vOut.texCoord);

	vec4 result = totalDiffuse + totalSpecular;
	result *= u_ObjectColor;
	result.a = 1.0;

	out_color = result;
}