#pragma once
#include<glm.hpp>
#include<gtx/rotate_vector.hpp>
class LightSpot
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, -1.0f);
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;


	float cutOff = 0.90f;
	float outerCutOff = 0.85f;

	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
	void UpdateDirection();
};

