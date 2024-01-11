#pragma once
#include<glm.hpp>
#include<gtx/rotate_vector.hpp>
class LightPoint
{
public:

	glm::vec3 position;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

	float constant;
	float linear;
	float quadratic;

	LightPoint(glm::vec3 _position, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));

};

