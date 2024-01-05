#pragma once
#include"Shader.h"
#include<glm.hpp>

class Material
{
public:
	Shader* shader;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	unsigned int diffuseTexture;
	unsigned int specularTexture;
	float shininess;

	Material(Shader* _shader, glm::vec3 _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess);
	Material(Shader* _shader, unsigned int _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess);
	Material(Shader* _shader, unsigned int _diffuse, glm::vec3 _ambient, unsigned int _specular, float _shininess);
};

