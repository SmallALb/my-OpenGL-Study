#version 460 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

uniform vec3 lightPosition;
uniform vec3 lightcolor;
uniform vec3 ambientcolor;

uniform sampler2D sampler;
uniform sampler2D specularMaskSapmler; 

uniform vec3 cameraPosition;
uniform float specularIntensity;
uniform float shiness;
uniform float k2;
uniform float k1;
uniform float kc;


void main() {
	vec3 viewDir = normalize(worldPosition - cameraPosition);
	vec3 DirectionN = normalize(worldPosition - lightPosition);
	vec3 objectColor = texture(sampler, uv).xyz;
	vec3 normalN = normalize(normal);

	float dist = length(worldPosition - lightPosition);
	float attenuation = 1.0 / (k2*dist*dist + k1 * dist + kc);

	//漫反射
	float diffuse = clamp(dot(-DirectionN, normalN), 0.0, 1.0);
	vec3 diffcuseColor = diffuse * lightcolor * objectColor;
	//高光反射
	vec3 reflectlight = normalize(reflect(DirectionN, normalN));
	float specular = max(dot(reflectlight, -viewDir), 0.0);
	specular = pow(specular, shiness);

	float specularMark = texture(specularMaskSapmler, uv).r;


	float doresult = dot(-DirectionN, normalN);
	float flag = step(0.0, doresult);
	vec3 specularcolor = lightcolor * specular * flag * specularIntensity * specularMark;

	vec3 ambient = objectColor * ambientcolor;

	vec3 finalColor =  attenuation * (diffcuseColor + specularcolor )+ ambient;

	FragColor = vec4(finalColor, 1.0);
}