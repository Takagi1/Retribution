#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main(){
	gl_Position = proj * view * model * vec4(position,0.0f, 1.0f);
	TexCoords = texCoords;
}