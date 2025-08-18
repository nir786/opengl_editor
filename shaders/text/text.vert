#version 330 core 
layout (location = 0 ) in vec4 vertex ; 
out vec2 TexCoords ; 
vec2 aUV = vertex.zw; 

float u_scale = 1.0f ; 



uniform mat4 projection ; 

void main ( ){ 
vec2 scaledPos = vertex.xy * u_scale +1.0f ; 
gl_Position = projection * vec4(scaledPos, 0.0, 1.0); 
TexCoords = vertex.zw; 
}
