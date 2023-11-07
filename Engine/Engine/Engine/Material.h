#pragma once
#include"Shader.h"
#include<glm.hpp>

class Material
{
public:
	Shader* shader;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	unsigned int diffuseTexture = 0;
	glm::vec3 specular;
	float shininess;

	Material(Shader* _shader, glm::vec3 _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess);
	Material(Shader* _shader, unsigned int _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess);
};

