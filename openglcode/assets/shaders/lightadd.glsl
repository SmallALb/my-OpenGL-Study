#version 460 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;

uniform vec3 Direction;
uniform vec3 lightcolor;
uniform sampler2D sampler;


void main() {
	vec3 normalin = normalize(normal);

	vec3 objectColor = texture(sampler, uv).xyz;

	vec3 lightDirN = normalize(Direction);

	float diffuse = clamp(dot(-lightDirN, normalin), 0.0, 1.0);


	vec3 finalColor = lightcolor  * objectColor * diffuse;

	FragColor = vec4(finalColor, 1.0);
}