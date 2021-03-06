#version 430
layout (location = 4) uniform int numLights;
uniform int isPointLight;
uniform float linearAtt;
uniform vec4 globalAmbient;
uniform sampler2D texSampler;
struct Material
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
float shininess;
};
uniform Material material;

struct PositionalLight
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};
layout (location = 5) uniform PositionalLight light[3];

in vec2 ftex;

in vec3 N[3];
in vec3 L[3];
in vec3 H[3];

in vec4 fpos;

void main()
{

vec3 ambient = vec3(0,0,0);
vec3 diffuse = vec3(0,0,0);
vec3 specular = vec3(0,0,0);

for(int f = 0; f < numLights; ++f)
{
	vec3 currentL = L[f];
	float att = 1.f;
	if(isPointLight == 1) //Si true
	{
		currentL = currentL - fpos.xyz;
		float distance = length(currentL);
		att = 1.f / (1.f + linearAtt * distance);
	}
	currentL = normalize(currentL);
	ambient = ambient + ((globalAmbient * material.ambient) + (light[f].ambient *material.ambient)).xyz;
	diffuse = diffuse + light[f].diffuse.xyz * material.diffuse.xyz* max(dot(currentL, N[f]), 0.0);
	diffuse = diffuse * att;
	float cosAlpha = dot(H[f],N[f]);
	specular = specular + material.specular.xyz * light[f].specular.xyz * pow(max(cosAlpha, 0.0f), material.shininess);
	specular = specular * att;
}

	vec4 finalColor = vec4((ambient + diffuse + specular), 1.0);
	gl_FragColor = texture2D(texSampler, ftex) * finalColor;
}