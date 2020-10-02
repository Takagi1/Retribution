#version 450 core

struct Light{
	vec3 lightPos;
	float ambient;
	float diffuse;
	vec3 lightColour;
};

struct Material {
	sampler2D diffuseMap;

	float shininess;
	float transparency;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;

uniform Material material;
uniform vec3 viewPos;

uniform Light light;

void main(){


	//ambient

	vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//diffuse

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//specular

	vec3 viewDir = normalize(viewPos - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour;

	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, material.transparency);
}