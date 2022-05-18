#version 430

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 norm_matrix;
uniform vec4 globalAmbient;

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vnormal;
layout (location = 2) in vec2 vtex;

out vec2 ftex;
out vec4 fcolor;

struct PositionalLight
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};
uniform PositionalLight light;

struct Material
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
float shininess;
};
uniform Material material;

void main() {
	vec4 color;
	
	vec4 P = mv * vec4(vnormal, 1.0);
	vec3 N = normalize((norm_matrix * vec4(vnormal, 1.0)).xyz);
	vec3 L = normalize(light.position - P.xyz);
	vec3 Eye = normalize(-P.xyz);
	vec3 R = reflect(-L,N);

	vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient *material.ambient)).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz* max(dot(N,L), 0.0);
	vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(R,Eye), 0.0f), material.shininess);

	fcolor = vec4((ambient + diffuse + specular), 1.0);
	gl_Position = mvp * vec4(vpos, 1);
	ftex = vtex;
}