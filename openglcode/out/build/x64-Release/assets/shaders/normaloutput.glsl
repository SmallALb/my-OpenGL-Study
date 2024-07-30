#version 460 core
out vec4 FragColor;


in vec3 normal;


void main() {
    vec3 norin = normalize(normal);
    vec3 norColor = clamp(norin, 0.0, 1.0);

    FragColor = vec4(norColor, 1.0);
}