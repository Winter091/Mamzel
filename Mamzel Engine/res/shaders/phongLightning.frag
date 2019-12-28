# version 440 core

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform float u_AmbientStrength;
//uniform float u_DiffuseStrength;
//uniform float u_SpecularStrength;

uniform vec3 u_LightPos;

in vec3 v_ObjectPos;
in vec3 v_Normal;

out vec4 out_color;

void main()
{
	// Ambient
	vec3 ambient = u_AmbientStrength * u_LightColor;
	
	// Diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPos - v_ObjectPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_LightColor;

	vec3 result = (ambient + diffuse) * u_ObjectColor;
	out_color = vec4(result, 1.0);
}