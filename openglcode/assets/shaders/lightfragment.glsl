#version 460 core
out vec4 FragColor;


struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutoff;
    float outerCutOff;
};

uniform Light light;

uniform Material material;

uniform vec3 viewPos;
in vec2 uv;
in vec4 color;
in vec3 pos;
in vec3 normal;
void main() {
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, uv));

    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    float attenuation = 0;
    vec3 lightDir = normalize(light.position - pos);

    float theta = dot(lightDir, normalize(-light.direction));
    vec3 norm = normalize(normal);
    float diff = max(dot(lightDir, norm), 0.0);
    diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uv));

    vec3 viewDir = normalize(viewPos - pos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    specular = light.specular * spec * vec3(texture(material.specular, uv));
    attenuation = 1.0 / (light.constant + light.linear * distance(light.position, pos) +light.quadratic * (distance(light.position, pos) * distance(light.position, pos)));
    float epsilon = (light.cutoff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;
    diffuse *= attenuation;
    specular *= attenuation;
    ambient *= attenuation;
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}

