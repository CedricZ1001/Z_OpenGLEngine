#pragma once
#include<glm.hpp>
#include<gtx/rotate_vector.hpp>
class LightDirectional
{
public:
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 color;

	LightDirectional(glm::vec3 _angles,glm::vec3 _color=glm::vec3(1.0f,1.0f,1.0f));
	void UpdateDirection();
};

