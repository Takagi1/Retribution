#version 450 core

layout (location = 0) in vec2 position;


uniform float size;
uniform mat4 proj;
uniform mat4 view;

void main(){
	vec4 temp = proj * view * vec4(position, 0.0f, 1.0f);
	gl_PointSize = size;
	gl_Position = temp;
}