#version 430
layout (location = 4) uniform int numLights;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 norm_matrix;

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vnormal;
layout (location = 2) in vec2 vtex;

struct PositionalLight
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};

layout (location = 5) uniform PositionalLight light[3];

out vec2 ftex;
out vec3 N[3];
out vec3 L[3];
out vec3 H[3];

out vec4 fpos;

void main() {

	vec4 P = mv * vec4(vnormal, 1.0); //Punto
	
	for(int i = 0; i < numLights; ++i)
	{
		N[i] = normalize((norm_matrix * vec4(vnormal, 1.0)).xyz); //varyingNormal
		L[i] = light[i].position - P.xyz; //varyingLightPos
		H[i] = normalize(L[i]) - P.xyz;
	}

	gl_Position = mvp * vec4(vpos, 1);
	ftex = vtex;
	fpos = mvp * vec4(vpos, 1);
}