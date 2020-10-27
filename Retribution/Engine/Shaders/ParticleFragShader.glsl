#version 450 core

out vec4 colour;

uniform vec4 tintColour;

void main(){

	vec4 tmpColour =  tintColour;
	colour = tmpColour;
}