#version 460 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;


uniform vec3 ambientcolor;

uniform sampler2D sampler;
uniform sampler2D specularMaskSapmler; 

uniform vec3 cameraPosition;

uniform vec3 targetDirection;

uniform float shiness;

struct DirectionLight {
	vec3 direction;
	vec3 color;
	float specularIntensity;
};

struct PointLight {
	vec3 position;
	vec3 color;
	float specularIntensity;
	float k2;
	float k1;
	float kc;
	int flag;
};

struct SpotLight {
	vec3 position;
	vec3 targetDirection;
	vec3 color;
	float inerline;
	float outerline;
	float specularIntensity;
};

#define PlightSum 6

uniform SpotLight spotlight;
uniform DirectionLight directionalLight;
uniform PointLight pointLights[PlightSum];


//����������
vec3 calculateDiffuse(vec3 normal, vec3 lightDir, vec3 lightColor, vec3 objectColor) {
	float diffuse = clamp(dot(-lightDir, normal), 0.0, 1.0);
	vec3 diffcuseColor = diffuse * lightColor * objectColor;

	return diffcuseColor;
}
//����߹�
vec3 calculateSpecular(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor, float specularIntensity) {
	vec3 reflectlight = normalize(reflect(lightDir, normal));
	float specular = max(dot(reflectlight, -viewDir), 0.0);
	specular = pow(specular, shiness);
	//�߹��ɰ�
	//float specularMark = texture(specularMaskSapmler, uv).r;
	//��ֹ���淴��
	float doresult = dot(-lightDir, normal);
	float flag = step(0.0, doresult);
	vec3 specularcolor = lightColor * specular * flag * specularIntensity;
	return specularcolor;
}
//����۹��
vec3 calculateSpotLight(vec3 normal, SpotLight light, vec3 viewDir) {
	vec3 objectColor = texture(sampler, uv).xyz;
	vec3 Direction = normalize(worldPosition - light.position);
	vec3 targetDir = normalize(light.targetDirection);
	float cGamma = dot(Direction, targetDir);
	float intensity = clamp((cGamma - light.outerline) / (light.inerline - light.outerline), 0.0, 1.0);
		//������
	vec3 diffcuseColor = calculateDiffuse(normal, Direction, light.color, objectColor);
	//�߹ⷴ��
	vec3 specularcolor = calculateSpecular(normal, Direction, viewDir, light.color, light.specularIntensity);

	return (diffcuseColor + specularcolor)* intensity;
}
//ƽ�й�   
vec3 calculateDirectionLight(vec3 normal, DirectionLight light, vec3 viewDir) {
	vec3 objectColor = texture(sampler, uv).xyz;
	vec3 lightDir = normalize(light.direction);

	//������
	vec3 diffcuseColor = calculateDiffuse(normal, lightDir, light.color, objectColor);
	//�߹ⷴ��
	vec3 specularcolor = calculateSpecular(normal, lightDir, viewDir, light.color, light.specularIntensity);
	return diffcuseColor + specularcolor;
}

//���Դ
vec3 calculatePointLight(vec3 normal, PointLight light, vec3 viewDir) {
	if (light.flag != 1) return vec3(0.0, 0.0, 0.0);
	vec3 objectColor = texture(sampler, uv).xyz;
	vec3 Direction = normalize(worldPosition - light.position);

	float distance = length(worldPosition - light.position);
	float attenuation = 1.0 / (light.kc + light.k1 * distance + light.k2 * (distance * distance));

	//������
	vec3 diffcuseColor = calculateDiffuse(normal, Direction, light.color, objectColor);
	//�߹ⷴ��
	vec3 specularcolor = calculateSpecular(normal, Direction, viewDir, light.color, light.specularIntensity);
	return (diffcuseColor + specularcolor)*attenuation;
}



void main() {
	vec3 result = vec3(0.0, 0.0, 0.0);

	vec3 viewDir = normalize(worldPosition - cameraPosition);
	vec3 DirectionN = normalize(worldPosition - spotlight.position);
	vec3 objectColor = texture(sampler, uv).xyz;
	vec3 normalN = normalize(normal);
	vec3 targetDirN = normalize(spotlight.targetDirection);

	result += calculateSpotLight(normalN, spotlight, viewDir);
	result += calculateDirectionLight(normalN, directionalLight, viewDir);
	for (int i = 0; i<PlightSum; i++) {result += calculatePointLight(normalN, pointLights[i], viewDir);}
	result += objectColor * ambientcolor;

	//vec3 finalColor =  (diffcuseColor + specularcolor ) * soptintensity + ambient;

	FragColor = vec4(result, 1.0);
}