# version 440 core

struct VertexOut
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoord;
};

struct Light
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
};

in VertexOut vOut;

uniform Light u_Light;

uniform vec3 u_ObjectColor;
uniform vec3 u_CameraPos;

uniform int u_UseTexture;
uniform sampler2D u_TextureSampler;

out vec4 out_color;

void main()
{
	// One ambient component
	vec3 result = vec3(u_Light.ambient);
	
	vec3 norm = normalize(vOut.normal);
	vec3 viewDir = normalize(u_CameraPos - vOut.fragPos);

	for (int i = 0; i < u_Light.count; i++)
	{	
		float distFormLight = length(u_Light.positions[i] - vOut.fragPos);
		float attenuation = 1.0 / ((u_Light.constant[i]) + (u_Light.linear[i] * distFormLight) + (u_Light.quadratic[i] * distFormLight * distFormLight));
		
		// Diffuse
		vec3 lightDir = normalize(u_Light.positions[i] - vOut.fragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = u_Light.diffuse * diff * u_Light.diffuseColor[i] * attenuation;

		// Specular
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(norm, halfwayDir), 0.0), 32);
		vec3 specular = u_Light.specular * spec * u_Light.specularColor[i] * attenuation;

		result += (diffuse + specular);
	}
	
	result *= u_ObjectColor;

	if (u_UseTexture == 0)
		out_color = vec4(result, 1.0);
	else
		out_color = texture(u_TextureSampler, vOut.texCoord) * vec4(result, 1.0);
}