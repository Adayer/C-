#version 430
layout (location = 4) uniform int numLights;
uniform vec4 globalAmbient;

in vec2 ftex;
uniform sampler2D texSampler;

in vec3 N[3];
in vec3 L[3];
in vec3 H[3];

struct PositionalLight
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};

layout (location = 5) uniform PositionalLight light[3];

struct Material
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
float shininess;
};
uniform Material material;

void main()
{

vec3 ambient = vec3(0,0,0);
vec3 diffuse = vec3(0,0,0);
vec3 specular = vec3(0,0,0);

for(int f = 0; f < numLights; ++f)
{
	ambient = ambient + ((globalAmbient * material.ambient) + (light[f].ambient *material.ambient)).xyz;
	diffuse = diffuse + light[f].diffuse.xyz * material.diffuse.xyz* max(dot(L[f], N[f]), 0.0);
	float cosAlpha = dot(H[f],N[f]);
	specular = specular + material.specular.xyz * light[f].specular.xyz * pow(max(cosAlpha, 0.0f), material.shininess);
}
	vec4 finalColor = vec4((ambient + diffuse + specular), 1.0);
	gl_FragColor = texture2D(texSampler, ftex) * finalColor;
}