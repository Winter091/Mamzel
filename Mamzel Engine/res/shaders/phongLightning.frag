# version 440 core

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform float u_AmbientStrength;
uniform float u_DiffuseStrength;
uniform float u_SpecularStrength;

uniform vec3 u_CameraPos;
uniform vec3 u_LightPositions[32];
uniform int u_LightCount;

in vec3 v_ObjectPos;
in vec3 v_Normal;

uniform int u_UseTexture;
uniform sampler2D u_TextureSampler;
in vec2 v_TexCoord;

out vec4 out_color;

void main()
{
	// One ambient component
	vec3 result = u_AmbientStrength * u_LightColor;
	
	for (int i = 0; i < u_LightCount; i++)
	{	
		// Diffuse
		vec3 norm = normalize(v_Normal);
		vec3 lightDir = normalize(u_LightPositions[i] - v_ObjectPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = u_DiffuseStrength * diff * u_LightColor;

		// Specular
		vec3 viewDir = normalize(u_CameraPos - v_ObjectPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = u_SpecularStrength * spec * u_LightColor;

		result += diffuse + specular;
	}
	
	result *= u_ObjectColor;

	if (u_UseTexture == 0)
		out_color = vec4(result, 1.0);
	else
		out_color = texture(u_TextureSampler, v_TexCoord) * vec4(result, 1.0);
}