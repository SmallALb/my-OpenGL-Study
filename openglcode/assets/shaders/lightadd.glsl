#version 460 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

uniform vec3 Direction;
uniform vec3 lightcolor;
uniform vec3 ambientcolor;
uniform sampler2D sampler;
uniform vec3 cameraPosition;
uniform float specularIntensity;

void main() {
	vec3 viewDir = normalize(worldPosition - cameraPosition);
	vec3 DirectionN = normalize(Direction);
	vec3 objectColor = texture(sampler, uv).xyz;
	vec3 normalN = normalize(normal);
	//漫反射
	float diffuse = clamp(dot(-DirectionN, normalN), 0.0, 1.0);
	vec3 diffcuseColor = diffuse * lightcolor * objectColor;
	//高光反射
	vec3 reflectlight = normalize(reflect(DirectionN, normalN));
	float specular = max(dot(reflectlight, -viewDir), 0.0);
	specular = pow(specular, 32);
	float doresult = dot(-DirectionN, normalN);
	float flag = step(0.0, doresult);
	vec3 specularcolor = lightcolor * specular * flag * specularIntensity;

	vec3 ambient = objectColor * ambientcolor;

	FragColor = vec4(diffcuseColor + specularcolor + ambient, 1.0);
}