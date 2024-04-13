#version 460 core
out vec4 FragColor;

uniform sampler2D blodsampler;
uniform sampler2D blacksampler;
uniform sampler2D glsssampler;
uniform float time;
in vec2 uv;
in vec4 color;
void main() {
   vec4 blodColor = texture(blodsampler, uv); 
   vec4 blackColor = texture(blacksampler, uv); 
   vec4 glsssColor = texture(glsssampler, uv);
   float weight = glsssColor.g;

   vec4 finalColor = mix(blackColor, blodColor, weight);
   FragColor = vec4(finalColor.rgba);
}