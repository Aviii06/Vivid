#version 330 core

in vec2 v_TexCoord;
in vec3 v_VertPos;
in vec3 v_CrntPos;
in vec3 v_Normal;
in mat3 v_TBN;

uniform vec3 LightDir;
// TODO: Have light intensity do something
uniform float LightIntensity;
uniform vec3 LightColor;

// Object Properties
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalMap;
uniform float Shininess;
uniform float AmbientStrength;
uniform float SpecularStrength;

out vec4 FragColor;

vec4 directionalLight(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 objectColor, vec3 lightColor)
{
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 ambient = AmbientStrength * lightColor;
	vec3 diffuse = max(dot(normal, lightDir), 0.0f) * lightColor;
	vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), Shininess) * SpecularStrength * lightColor;

	vec4 color = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
	return color;
}

void main()
{
	vec3 normal = texture(NormalMap, v_TexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(v_TBN * normal);
	vec3 objectColor = texture(DiffuseTexture, v_TexCoord).rgb;

	vec3 lightDir = normalize(LightDir);
	vec3 viewDir = normalize(-v_VertPos);
	FragColor = directionalLight(normal, lightDir, viewDir, objectColor, LightColor);
}

//////////
