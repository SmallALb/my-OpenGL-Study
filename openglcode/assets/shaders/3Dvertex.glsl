#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 normal;
uniform vec3 moveUV;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec4 color;
out vec3 pos;
out vec3 nor;
out vec2 uv;
void main() {
   gl_Position = projection* view* model* vec4(aPos.x, aPos.y, aPos.z, 1.0);
   color = aColor;
   vec4 wpos = model* vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vec3 pos =vec3(wpos.x, wpos.y, wpos.z);
   nor = mat3(transpose(inverse(model))) * normal;
   uv = aUV + moveUV.xy;
}